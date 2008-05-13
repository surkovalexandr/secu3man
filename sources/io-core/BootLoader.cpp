 /****************************************************************
 *       SECU-3  - An open source, free engine control unit
 *    Designed by Alexey A. Shabelnikov. Ukraine, Gorlovka 2007.
 *       Microprocessors systems - design & programming.
 *    contacts:
 *              http://secu-3.narod.ru
 *              ICQ: 405-791-931
 ****************************************************************/

#include "stdafx.h"
#include "BootLoader.h"
#include "ccomport.h"

#define EEPROM_RD_BLOCKS 8   //���������� ������ ������ EEPROM,����� ������ ���� �������� ������
#define EEPROM_WR_BLOCKS 16  //���������� ������ ������ EEPROM,����� ������ ���� �������� ������


//-----------------------------------------------------------------------
CBootLoader::CBootLoader()
: m_pEventHandler(NULL)
{
  m_p_port      = NULL;
  m_hThread     = NULL;
  m_ThreadId    = 0;
  m_hAwakeEvent = NULL;
  m_ErrorCode   = 0; 

  m_ThreadBusy  = false;
  m_is_thread_must_exit = false;
  m_work_stoped = true;
  m_uart_speed  = CBR_9600;
}

//-----------------------------------------------------------------------
CBootLoader::~CBootLoader()
{
}

//-----------------------------------------------------------------------
//��������������� ������� ��� ������ ����� �������� FLASH
//n_page - ����� �������� ��� ������
//o_buf  - ����� ��� ��������� � ���� ���������� ������ (������ ������)
//total_size,current - ��� ���������� UI
bool CBootLoader::FLASH_ReadOnePage(int n_page,BYTE* o_buf,int total_size,int* current)
{
  BYTE t_buf[2048];
  BYTE t_byte = 0;
  int  block_size = FLASH_PAGE_SIZE * 2;

  t_buf[0] = '!'; //!RNN
  t_buf[1] = 'R';
  CNumericConv::Bin8ToHex(n_page,&t_buf[2]); //�������� ����� �������� (t_buf[2],t_buf[3])
  t_buf[4] = 0;  //��������� ������
  m_p_port->SendASCII((char*)t_buf); //������� ������� ������ �������� 

  //������ ���������� �������� ������ ��������
  if (!m_p_port->RecvByte(&t_byte))
  {
	m_ErrorCode = BL_ERROR_NOANSWER;
    return false; //��� ������ ���������� ������
  }

  if (t_byte!='<')
  {
	m_ErrorCode = BL_ERROR_WRONG_DATA;
	return false; //��� ������ ���������� ������
  }

  m_pEventHandler->OnUpdateUI(m_opdata.opcode,total_size,++(*current));  //1 ���� �������

  if (!m_p_port->RecvBlock(t_buf,block_size))  //������� ��������� ��������
  {
    m_ErrorCode = BL_ERROR_NOANSWER; 
	return false; //����� ������ �������� - ��� ������ ���������� ������
  }

  (*current)+=block_size;
  m_pEventHandler->OnUpdateUI(m_opdata.opcode,total_size,*current); //��������� �������� �������

  if (!CNumericConv::HexArrayToBin(t_buf,o_buf,FLASH_PAGE_SIZE))
  {
    m_ErrorCode = BL_ERROR_WRONG_DATA;
    return false;
  }

  if (!m_p_port->RecvBlock(t_buf,2))  //CS - ��� �������
  {
    m_ErrorCode = BL_ERROR_NOANSWER;		   
    return false;
  }

  *current+=2;
  m_pEventHandler->OnUpdateUI(m_opdata.opcode,total_size,*current);  //�������� �������

  if (!CNumericConv::Hex8ToBin(t_buf,&t_byte))   //t_buf -> symbol
  {
	m_ErrorCode = BL_ERROR_WRONG_DATA;
	return false;
  }

  if (CNumericConv::CheckSum_8_xor(o_buf,FLASH_PAGE_SIZE)!=t_byte) //��������� ����������� �����
  {
    m_ErrorCode = BL_ERROR_CHKSUM;
	return false; //����������� ����� �� ���������
  }
 return true; //All are OK
}


//-----------------------------------------------------------------------
DWORD WINAPI CBootLoader::BackgroundProcess(LPVOID lpParameter)
{
  CBootLoader* p_boot = (CBootLoader*)lpParameter;
  CComPort* p_port = p_boot->m_p_port;
  IBLDEventHandler* pEventHandler = NULL;
  int opcode = 0, i = 0, j = 0, k = 0; 
  int block_size,total_size,current;
  BYTE symbol = 0;  //��� �������� ������� '<' 
  BYTE raw[2048];   //������ � ������� ��� ����� ����
  BYTE t_buf[1024];

  while(1) 
  {
	  WaitForSingleObject(p_boot->m_hAwakeEvent,INFINITE); //sleep until enters a new command

	  if (p_boot->m_is_thread_must_exit)
		  break;  //��������� ������� ���������� ������ ������

      pEventHandler = p_boot->m_pEventHandler;
      ASSERT(pEventHandler); //����� ��� ��� ��������/������������ �������, ���������� ����������� ���������� �������! 

	  opcode = p_boot->m_opdata.opcode;
	  switch(opcode)  //��������� ������
	  {
	   //========================================================================================= 
	   case BL_OP_READ_FLASH:    //������ FLASH
		   p_boot->m_ErrorCode  = 0;  //����� ����������� ����� ������� ���������� �������� ������
		   symbol     = 0;
		   pEventHandler->OnBegin(p_boot->m_opdata.opcode,true);
		   block_size = FLASH_PAGE_SIZE * 2;
		   current    = 0;

		   k = p_boot->m_opdata.size;
           i = k % FLASH_PAGE_SIZE;
		   j = k / FLASH_PAGE_SIZE;  //���������� �������

		   if (i > 0)
			   ++j;

		   total_size = j * (block_size + 1 + 2);   //1 byte - '<' + 2 bytes - CS
		   pEventHandler->OnUpdateUI(opcode,total_size,current);


		   for(i = 0; i < j; i++) //����: ���������� �������
		   {
             if (false == p_boot->FLASH_ReadOnePage(i,p_boot->m_opdata.data+(i*FLASH_PAGE_SIZE),total_size,&current))
				 break; //������!
		   }//for
		   pEventHandler->OnEnd(p_boot->m_opdata.opcode,p_boot->Status());
	       p_boot->m_opdata.opcode = 0; 	   
		   break;

	   //========================================================================================= 
       case BL_OP_WRITE_FLASH:   //������ FLASH
		   p_boot->m_ErrorCode  = 0;  //����� ����������� ����� ������� ���������� �������� ������
		   symbol     = 0;
		   pEventHandler->OnBegin(p_boot->m_opdata.opcode,true);
		   block_size = FLASH_PAGE_SIZE * 2;
		   current    = 0;
		   int incomplete_page_bytes;
		   int total_page_number;
		   
           incomplete_page_bytes = p_boot->m_opdata.size % FLASH_PAGE_SIZE; //���������� ���� � �������� �������� (����� 0 ���� ���������� ������ ������ ������� ��������)
		   total_page_number = p_boot->m_opdata.size / FLASH_PAGE_SIZE;  //���������� �������

		   if (incomplete_page_bytes > 0) //���� �������� ��������
			   ++total_page_number;               //��������� ��� �� ������������� ��������

		   total_size = total_page_number * (block_size + 1 + 2);   //1 byte - '<' + 2 bytes - CS

		   if (incomplete_page_bytes > 0) //���� �� ������ ��������, �� �� ������ �� ��������� � ���������� ������
		   {
			   total_size+= (block_size + 1 + 2);
		   }
           
		   pEventHandler->OnUpdateUI(opcode,total_size,current);


		   for(i = 0; i < total_page_number; i++) //����: ���������� �������
		   {             		

             if ((i==total_page_number-1)&&(incomplete_page_bytes > 0)) 
			 {//���� �������� �������� � �� ������ �� ������������

               if (false == p_boot->FLASH_ReadOnePage(i,t_buf,total_size,&current))
				   break;
               //���������� ����� �� ����������� �������� � ��������� �������  
			   memcpy(t_buf,p_boot->m_opdata.data+(i*FLASH_PAGE_SIZE),incomplete_page_bytes);			   
			 }
			 else
			 { //�������� �������� ���� ��� �� �� ��� ��� �� �����: �������� ������ �������� � ��������� ������� 			 
               memcpy(t_buf,p_boot->m_opdata.data+(i*FLASH_PAGE_SIZE),FLASH_PAGE_SIZE);
			 }

             raw[0] = '!';	//!PNN - 4 �����		 
			 raw[1] = 'P';			 
			 CNumericConv::Bin8ToHex(i,&raw[2]); //�������� ����� �������� NN			 
			 raw[4] = 0;
             p_port->SendASCII((char*)raw); //������� ������� ������ �������� 
             
			 //������ ���������� ��������� ���������� �������� �������� (��������� ��)
			 Sleep(FLASH_PG_ERASE_DELAY);
			 
	  	     //��������������� ����� � HEX-������� (raw ����� ��������� HEX-�������)
             CNumericConv::BinToHexArray(t_buf,raw,FLASH_PAGE_SIZE);
			 raw[block_size] = 0; //��������� ������

             p_port->SendASCII((char*)raw); //������� ������ �������� 
			 
			 current+=block_size;
	  	     pEventHandler->OnUpdateUI(opcode,total_size,current);  //���� �������� ��������
			
			 //������ ����� ��������� ���������� ������ � ��� ������� ����������� �����
			 //������ ���������� �������� ������
			 if (!p_port->RecvByte(&symbol))
			 {
			   p_boot->m_ErrorCode = BL_ERROR_NOANSWER;
			   break; //��� ������ ���������� ������
			 }

		     if (symbol!='<')
			 {
			   p_boot->m_ErrorCode = BL_ERROR_WRONG_DATA;
			   break; //��� ������ ���������� ������
			 }

	 	     pEventHandler->OnUpdateUI(opcode,total_size,++current);  //1 ���� �������

 		     if (!p_port->RecvBlock(raw,2))  //CS
			 {
			   p_boot->m_ErrorCode = BL_ERROR_NOANSWER;		   
			   break;
			 }

		     current+=2;
		     pEventHandler->OnUpdateUI(opcode,total_size,current);   //2 ����� ��������

			 if (!CNumericConv::Hex8ToBin(raw,&symbol))
			 {
			   p_boot->m_ErrorCode = BL_ERROR_WRONG_DATA;
			   break;
			 }

			 if (CNumericConv::CheckSum_8_xor(t_buf,FLASH_PAGE_SIZE)!=symbol)
			 {
			   p_boot->m_ErrorCode = BL_ERROR_CHKSUM; //����������� ����� �� ���������
			   break;
			 }

		   }//for

		   pEventHandler->OnEnd(p_boot->m_opdata.opcode,p_boot->Status());
	       p_boot->m_opdata.opcode = 0; 	   
		   break;

	   //========================================================================================= 
       case BL_OP_READ_EEPROM:    //������ EEPROM
		   p_boot->m_ErrorCode  = 0;  //����� ���������� ����� ������� ���������� �������� ������
		   symbol     = 0;
	   	   block_size = (EEPROM_SIZE*2)/EEPROM_RD_BLOCKS;
		   total_size = (EEPROM_SIZE*2)+1+2;   //1 byte - '<' + 2 bytes - CS
		   current    = 0;

		   pEventHandler->OnBegin(p_boot->m_opdata.opcode,true);
		   pEventHandler->OnUpdateUI(opcode,total_size,current);
           p_port->SendASCII("!J"); //������
		   if (!p_port->RecvByte(&symbol))
		   {
			   p_boot->m_ErrorCode = BL_ERROR_NOANSWER;
			   goto finish_read_eeprom;  //������ �������� ����������� �������
		   }  
		   if (symbol!='<')
		   {
			   p_boot->m_ErrorCode = BL_ERROR_WRONG_DATA;
			   goto finish_read_eeprom;
		   }

		   pEventHandler->OnUpdateUI(opcode,total_size,++current);

            for(i = 0; i < EEPROM_RD_BLOCKS; i++) //��������� ������ �� ������
			{			   
		       if (!p_port->RecvBlock(raw+(i*block_size),block_size))  //receive the data
			   {
				   p_boot->m_ErrorCode = BL_ERROR_NOANSWER; 
				   goto finish_read_eeprom;//����� ������ �������� - ��� ������ ���������� ������
			   }
			   current+=block_size;
			   pEventHandler->OnUpdateUI(opcode,total_size,current);
			}//for

            if (!CNumericConv::HexArrayToBin(raw,p_boot->m_opdata.data,EEPROM_SIZE))
			{
				p_boot->m_ErrorCode = BL_ERROR_WRONG_DATA;
				goto finish_read_eeprom;
			}

			pEventHandler->OnUpdateUI(opcode,total_size,current);

		    if (!p_port->RecvBlock(raw,2))  //CS
			{
				p_boot->m_ErrorCode = BL_ERROR_NOANSWER;		   
				goto finish_read_eeprom;
			}

		    current+=2;
		    pEventHandler->OnUpdateUI(opcode,total_size,current);

            if (!CNumericConv::Hex8ToBin(raw,&symbol))
			{
				p_boot->m_ErrorCode = BL_ERROR_WRONG_DATA;
				goto finish_read_eeprom;
			}

            if (CNumericConv::CheckSum_8_xor(p_boot->m_opdata.data,EEPROM_SIZE)!=symbol)
			   p_boot->m_ErrorCode = BL_ERROR_CHKSUM;

finish_read_eeprom:
		   pEventHandler->OnEnd(p_boot->m_opdata.opcode,p_boot->Status());
	       p_boot->m_opdata.opcode = 0; 	   
		   break;

       //========================================================================================= 
       case BL_OP_WRITE_EEPROM:    //������ EEPROM
		   p_boot->m_ErrorCode  = 0;  //����� ���������� ����� ������� ���������� �������� ������
		   symbol     = 0;
	   	   block_size = (EEPROM_SIZE*2)/EEPROM_WR_BLOCKS;
		   total_size = (EEPROM_SIZE*2)+1+2;   //1 byte - '<' + 2 bytes - CS
		   current    = 0;

		   pEventHandler->OnBegin(p_boot->m_opdata.opcode,true);
		   pEventHandler->OnUpdateUI(opcode,total_size,current);
           p_port->SendASCII("!W");  //������

		   //��������������� ����� � HEX-�������
           CNumericConv::BinToHexArray(p_boot->m_opdata.data,raw,EEPROM_SIZE);
		
		    k = 0;
            for(i = 0; i < EEPROM_WR_BLOCKS; i++) //�������� ������ �� ������
			{			   
				for(j = 0; j < block_size; j++) //����: �� ������ ���� �� 2 �������
				{
                  p_port->SendByte(raw[k]); 
				  Sleep(EEPROM_WR_DELAY_MULTIPLIER);
				  k++;
				}
			   current+=block_size;
			   pEventHandler->OnUpdateUI(opcode,total_size,current);
			}//for

           //��������� �����
			if (!p_port->RecvByte(&symbol))
			{
			  p_boot->m_ErrorCode = BL_ERROR_NOANSWER;
			  goto finish_write_eeprom; //������ �������� ����������� �������
			}

		    if (symbol!='<')  //������ �� �������� ���������� (���� � ��� ������ �������)
			{
			  p_boot->m_ErrorCode = BL_ERROR_WRONG_DATA;
			  goto finish_write_eeprom;
			}

		    pEventHandler->OnUpdateUI(opcode,total_size,++current);

		    if (!p_port->RecvBlock(raw,2))  //CS
			{
		  	  p_boot->m_ErrorCode = BL_ERROR_NOANSWER;		   
			  goto finish_write_eeprom;
			}

		    current+=2;
		    pEventHandler->OnUpdateUI(opcode,total_size,current);

            if (!CNumericConv::Hex8ToBin(raw,&symbol))
			{
		  	  p_boot->m_ErrorCode = BL_ERROR_WRONG_DATA;
			  goto finish_write_eeprom;
			}

            if (CNumericConv::CheckSum_8_xor(p_boot->m_opdata.data,EEPROM_SIZE)!=symbol)
		 	  p_boot->m_ErrorCode = BL_ERROR_CHKSUM;

finish_write_eeprom:
		   pEventHandler->OnEnd(p_boot->m_opdata.opcode,p_boot->Status());
	       p_boot->m_opdata.opcode = 0; //����� ���� ��������	   
		   break;


       //========================================================================================= 
       case BL_OP_READ_SIGNATURE:  //������ ����������� ���������� � ����������
		   p_boot->m_ErrorCode  = 0;
		   symbol = 0;
		   total_size = BL_SIGNATURE_STR_LEN+1; //1 byte - '<'
		   current    = 0;
		   pEventHandler->OnBegin(p_boot->m_opdata.opcode,true);
		   pEventHandler->OnUpdateUI(opcode,total_size,current);
           p_port->SendASCII("!I");
		   if (!p_port->RecvByte(&symbol))
		   {
			 p_boot->m_ErrorCode = BL_ERROR_NOANSWER;
			 goto finish_read_signature; //��� ������ ���������� ������
		   }
		   if (symbol!='<')
		   {
			 p_boot->m_ErrorCode = BL_ERROR_WRONG_DATA;
		   }
		   else
		   {
		    pEventHandler->OnUpdateUI(opcode,total_size,++current);

		    if (!p_port->RecvBlock(p_boot->m_opdata.data,BL_SIGNATURE_STR_LEN))
			   p_boot->m_ErrorCode = BL_ERROR_NOANSWER;

			current+=BL_SIGNATURE_STR_LEN;
			pEventHandler->OnUpdateUI(opcode,total_size,current);
		   }
finish_read_signature:
		   pEventHandler->OnEnd(p_boot->m_opdata.opcode,p_boot->Status());
	       p_boot->m_opdata.opcode = 0; 	   
		   break;

	   //========================================================================================= 
       case BL_OP_EXIT:            //����� �� ����������
		   p_boot->m_ErrorCode  = 0;
		   symbol = 0;
		   total_size = 1+1; //1 byte - '<', 1 byte - '@'
		   current    = 0;
		   pEventHandler->OnBegin(p_boot->m_opdata.opcode,true);
		   pEventHandler->OnUpdateUI(opcode,total_size,current);
		   //�������� �������
           p_port->SendASCII("!T");
		   //��������� � ����������� �����
		   if (!p_port->RecvByte(&symbol))
		   {
		     p_boot->m_ErrorCode = BL_ERROR_NOANSWER;
			 goto finish_exit;
		   }
		   if (symbol!='<')
		   {
			 p_boot->m_ErrorCode = BL_ERROR_WRONG_DATA;
			 goto finish_exit;
		   }
		   else
		   {
	 	     pEventHandler->OnUpdateUI(opcode,total_size,++current); //��������� � �������� ������� �����
		   }
           
		   symbol = 0;
		   //������ ����
		   if (!p_port->RecvByte(&symbol))
		   {
		     p_boot->m_ErrorCode = BL_ERROR_NOANSWER;
			 goto finish_exit;
		   }
		   if (symbol!='<')
		   {
			 p_boot->m_ErrorCode = BL_ERROR_WRONG_DATA;			 
		   }
		   else
		   {
	 	     pEventHandler->OnUpdateUI(opcode,total_size,++current); //��������� � �������� ������� �����
		   }

finish_exit:
		   pEventHandler->OnEnd(p_boot->m_opdata.opcode,p_boot->Status());
	       p_boot->m_opdata.opcode = 0; 	   
		   break;

	  }//switch
	  ResetEvent(p_boot->m_hAwakeEvent); //���������� ������� ����������� ������ - �� ����� ������ � ������
      p_boot->m_ThreadBusy = false;      //operation is completed - thread is not busy

  }//while

 return 0;
}


//-----------------------------------------------------------------------
//������� ������ Initialize ������ ��������������� ����� ���� ������� 
bool CBootLoader::Terminate(void)
{
	bool status=true;
	DWORD ExitCode;
	ExitCode = 0;

	m_is_thread_must_exit = true;
    SetEvent(m_hAwakeEvent);       //������� ����� �� ������ - ��������� � ����� ����������

	int i = 0;
	do  //� ���� �� �� ����� ���������� �� ��������, ����� ��������� ����� ���������� ���... 
	{
		if (i >= 20)
			break;
		Sleep(50);
		GetExitCodeThread(m_hThread,&ExitCode);
		++i;
	}while(ExitCode == STILL_ACTIVE);

    if (!TerminateThread(m_hThread,0))
		status = false;

	if (!CloseHandle(m_hAwakeEvent))
		status = false;

	m_ThreadBusy = false;
	return status;
}


//-----------------------------------------------------------------------
//exception: xThread 
bool CBootLoader::Initialize(CComPort* p_port, const DWORD uart_seed)
{
  if (!p_port)
	  return false;
  m_p_port = p_port;

  m_hAwakeEvent = CreateEvent(NULL,TRUE,FALSE,NULL);
  if (m_hAwakeEvent==NULL)
  {
     return false;        //event creation error
  }

  m_hThread = CreateThread(0,0,(LPTHREAD_START_ROUTINE)BackgroundProcess,(void*)this,0,&m_ThreadId);  
  if (m_hThread==NULL)
  {
     throw xThread();     
	 return false;        //thread creation error
  }

  m_is_thread_must_exit = false;
  m_uart_speed = uart_seed;

  return true;
}


//-----------------------------------------------------------------------
//��������� ��� ������� �� ������������
bool CBootLoader::IsOpcodeValid(const int opcode)
{
	switch(opcode) //��������� � ����������� ������ ������
	{
	case BL_OP_READ_FLASH:
    case BL_OP_WRITE_FLASH:
    case BL_OP_READ_EEPROM:
    case BL_OP_WRITE_EEPROM:
    case BL_OP_READ_SIGNATURE:
    case BL_OP_EXIT:
		return true;
    default:
		return false;
	}//switch
}


//-----------------------------------------------------------------------
//��������� ��������� �������� �� ����������. ��� ������� �� ��������� ��������� �� �����, � ������ 
//�������������� ������, ��������� ���������� �������� � ����� ���������� ����������.
// io_data - ����� ��� ������/������ ������ 
// i_size  - ������ ������ � ������ 
//Return: �������� �������� �� ���������� ������� - true, ����� - false
bool CBootLoader::StartOperation(const int opcode,BYTE* io_data,int i_size)
{
    if (true==m_work_stoped) 
		return false;

	if (m_ThreadBusy)              //�� ��������� ��������� ���������� ������� ?
	{
		m_pEventHandler->OnBegin(opcode,false);
		return false;              //������ ������� �� ���������� ����� ������� (�������)
	}
   
	if (!IsOpcodeValid(opcode))
        return false;              //������������ ����� 

	m_ThreadBusy = true;           //set busy flag - since current moment thread is busy

	//��������� ������ � ������� ������ ����������� ������
	m_opdata.opcode = opcode;
	m_opdata.data   = io_data;     
	m_opdata.size   = i_size;

	m_ErrorCode = 0;
	SetEvent(m_hAwakeEvent);       //������� ����� �� ������ - ������� ����� ���������� :-)
   
 return true;
} 

//-----------------------------------------------------------------------
void CBootLoader::SwitchOn(bool state)
{
	COMMTIMEOUTS timeouts;
	float ms_need_for_one_byte; 
	
    //���-�� �� ����������� ��� ������/�������� ������ �����	
	ms_need_for_one_byte = CComPort::ms_need_for_one_byte_8N1(m_uart_speed); 

   if (state)
   {
      //����� �������������� ������ ���������� ���������� ��������� (����� �������� ��� ������ � ��������) 
      m_p_port->Purge();

	  m_p_port->AccessDCB()->fAbortOnError = FALSE;     //����������� �������� ��� ������
	  m_p_port->AccessDCB()->BaudRate = m_uart_speed;   //��� ������ � ����������� ���� ��������
	  m_p_port->SetState();
   
	  //������ ���������� ��������� �������� (� ������� ��� � �� ����� ������ � ���� ���������)
	  timeouts.ReadIntervalTimeout         = 200; 
	  timeouts.ReadTotalTimeoutMultiplier  = 200;
      timeouts.ReadTotalTimeoutConstant    = 200; 
	  timeouts.WriteTotalTimeoutConstant   = 200;
      timeouts.WriteTotalTimeoutMultiplier = 200;
	  m_p_port->SetTimeouts(&timeouts);	   
	  m_work_stoped = false;
	  Sleep(CNumericConv::Round(ms_need_for_one_byte * 5));
   }
   else
   {
    m_work_stoped = true;
	Sleep(CNumericConv::Round(ms_need_for_one_byte * 5));
   }
}

//-----------------------------------------------------------------------