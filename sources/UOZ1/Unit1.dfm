object Form1: TForm1
  Left = 267
  Top = 127
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = '�������������� ���� ���'
  ClientHeight = 364
  ClientWidth = 621
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  Icon.Data = {
    0000010002002020100000000000E80200002600000010101000000000002801
    00000E0300002800000020000000400000000100040000000000800200000000
    0000000000000000000000000000000000000000800000800000008080008000
    00008000800080800000C0C0C000808080000000FF0000FF000000FFFF00FF00
    0000FF00FF00FFFF0000FFFFFF00000000000000000000000000000000000000
    0000000000000000000000000000000000000000000000000000000000000000
    0000000000000000000000000000000000000000000000000000000000000000
    00FFFFF000000000000000000000000000FFF000000000000000000000000000
    00FFF00000000000000000000000000000F00F00000000000000000000000000
    000000F00000000000000000000000000000000F000000000000000000000000
    00000000F000000000000F0000000000000000000F000000000000FF00000000
    0000000000FFFFFFFFFFFFFFF00000000000000000FBB000000000FF00000000
    0000000000F0BB0000000F00000000000000000000F00BB00000000000000000
    0000000000F000BBB0000000000000000000000000F0000BBBBBBB0000000000
    0000000000F000000BBBBB00000000000000000000F000000000000000000000
    0000000000F0000000000000000000000000000000F000000000000000000000
    00000000F0F0F000000000000000000000000000F0F0F0000000000000000000
    000000000FFF00000000000000000000000000000FFF00000000000000000000
    0000000000F00000000000000000000000000000000000000000000000000000
    0000000000000000000000000000000000000000000000000000000000000000
    0000000000000000000000000000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
    FFFFFC1FFFFFFC7FFFFFFC7FFFFFFDBFFFFFFFDFFFFFFFEFFFFFFFF7FFBFFFFB
    FFCFFFFC0007FFFC7FCFFFFD3FBFFFFD9FFFFFFDC7FFFFFDE03FFFFDF83FFFFD
    FFFFFFFDFFFFFFFDFFFFFFF57FFFFFF57FFFFFF8FFFFFFF8FFFFFFFDFFFFFFFF
    FFFFFFFFFFFFFFFFFFFFFFFFFFFF280000001000000020000000010004000000
    0000C00000000000000000000000000000000000000000000000000080000080
    000000808000800000008000800080800000C0C0C000808080000000FF0000FF
    000000FFFF00FF000000FF00FF00FFFF0000FFFFFF0000000000000000000000
    0000000000000000000000000000000EE00000000000000EE000000000000000
    0E0000000000000000E000000E000000000EEEEEEEE00000000EB0000E000000
    000E0B0000000000000E00BBBB000000000E00000000000000EEE00000000000
    000E0000000000000000000000000000000000000000FFFF0000FFFF0000FFFF
    0000E7FF0000E7FF0000FBFF0000FDFB0000FE010000FE7B0000FEBF0000FEC3
    0000FEFF0000FC7F0000FEFF0000FFFF0000FFFF0000}
  OldCreateOrder = False
  Position = poDesktopCenter
  OnClose = FormClose
  PixelsPerInch = 96
  TextHeight = 13
  object Chart1: TChart
    Left = 0
    Top = 8
    Width = 585
    Height = 353
    AllowPanning = pmNone
    AllowZoom = False
    BackWall.Brush.Color = clWhite
    BackWall.Brush.Style = bsClear
    Title.Text.Strings = (
      '������ ��� �� �����')
    OnClickSeries = Chart1ClickSeries
    BottomAxis.Title.Caption = '������� (���-1)'
    LeftAxis.Automatic = False
    LeftAxis.AutomaticMaximum = False
    LeftAxis.AutomaticMinimum = False
    LeftAxis.ExactDateTime = False
    LeftAxis.Maximum = 60
    LeftAxis.Minimum = -17.5
    LeftAxis.Title.Caption = '��� (����.)'
    Legend.Visible = False
    View3D = False
    TabOrder = 0
    OnMouseMove = Chart1MouseMove
    OnMouseUp = Chart1MouseUp
    object Series1: TLineSeries
      Marks.ArrowLength = 8
      Marks.Frame.Visible = False
      Marks.Style = smsValue
      Marks.Transparent = True
      Marks.Visible = False
      SeriesColor = 16777088
      ValueFormat = '#,##0.#'
      Pointer.InflateMargins = True
      Pointer.Style = psRectangle
      Pointer.Visible = True
      XValues.DateTime = False
      XValues.Name = 'X'
      XValues.Multiplier = 1
      XValues.Order = loAscending
      YValues.DateTime = False
      YValues.Name = 'Y'
      YValues.Multiplier = 1
      YValues.Order = loNone
    end
    object Series2: TLineSeries
      Marks.ArrowLength = 8
      Marks.Frame.Visible = False
      Marks.Style = smsValue
      Marks.Transparent = True
      Marks.Visible = True
      SeriesColor = 8421631
      ValueFormat = '#,##0.#'
      Pointer.InflateMargins = True
      Pointer.Style = psRectangle
      Pointer.Visible = True
      XValues.DateTime = False
      XValues.Name = 'X'
      XValues.Multiplier = 1
      XValues.Order = loAscending
      YValues.DateTime = False
      YValues.Name = 'Y'
      YValues.Multiplier = 1
      YValues.Order = loNone
    end
  end
  object ButtonAngleUp: TBitBtn
    Left = 592
    Top = 88
    Width = 25
    Height = 33
    TabOrder = 1
    OnClick = ButtonAngleUpClick
    Glyph.Data = {
      9E050000424D9E05000000000000360400002800000011000000120000000100
      0800000000006801000000000000000000000001000000000000000000000000
      80000080000000808000800000008000800080800000C0C0C000C0DCC000F0CA
      A6000020400000206000002080000020A0000020C0000020E000004000000040
      20000040400000406000004080000040A0000040C0000040E000006000000060
      20000060400000606000006080000060A0000060C0000060E000008000000080
      20000080400000806000008080000080A0000080C0000080E00000A0000000A0
      200000A0400000A0600000A0800000A0A00000A0C00000A0E00000C0000000C0
      200000C0400000C0600000C0800000C0A00000C0C00000C0E00000E0000000E0
      200000E0400000E0600000E0800000E0A00000E0C00000E0E000400000004000
      20004000400040006000400080004000A0004000C0004000E000402000004020
      20004020400040206000402080004020A0004020C0004020E000404000004040
      20004040400040406000404080004040A0004040C0004040E000406000004060
      20004060400040606000406080004060A0004060C0004060E000408000004080
      20004080400040806000408080004080A0004080C0004080E00040A0000040A0
      200040A0400040A0600040A0800040A0A00040A0C00040A0E00040C0000040C0
      200040C0400040C0600040C0800040C0A00040C0C00040C0E00040E0000040E0
      200040E0400040E0600040E0800040E0A00040E0C00040E0E000800000008000
      20008000400080006000800080008000A0008000C0008000E000802000008020
      20008020400080206000802080008020A0008020C0008020E000804000008040
      20008040400080406000804080008040A0008040C0008040E000806000008060
      20008060400080606000806080008060A0008060C0008060E000808000008080
      20008080400080806000808080008080A0008080C0008080E00080A0000080A0
      200080A0400080A0600080A0800080A0A00080A0C00080A0E00080C0000080C0
      200080C0400080C0600080C0800080C0A00080C0C00080C0E00080E0000080E0
      200080E0400080E0600080E0800080E0A00080E0C00080E0E000C0000000C000
      2000C0004000C0006000C0008000C000A000C000C000C000E000C0200000C020
      2000C0204000C0206000C0208000C020A000C020C000C020E000C0400000C040
      2000C0404000C0406000C0408000C040A000C040C000C040E000C0600000C060
      2000C0604000C0606000C0608000C060A000C060C000C060E000C0800000C080
      2000C0804000C0806000C0808000C080A000C080C000C080E000C0A00000C0A0
      2000C0A04000C0A06000C0A08000C0A0A000C0A0C000C0A0E000C0C00000C0C0
      2000C0C04000C0C06000C0C08000C0C0A000F0FBFF00A4A0A000808080000000
      FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00FFFFFFFFFFFF
      FFFFFFFFFFFFFFFFFFFFFF000000FFFFFFFFFFFF0202020202FFFFFFFFFFFF00
      0000FFFFFFFFFFFF0202020202FFFFFFFFFFFF000000FFFFFFFFFFFF02020202
      02FFFFFFFFFFFF000000FFFFFFFFFFFF0202020202FFFFFFFFFFFF000000FFFF
      FFFFFFFF0202020202FFFFFFFFFFFF000000FFFFFFFFFFFF0202020202FFFFFF
      FFFFFF000000FFFFFFFFFFFF0202020202FFFFFFFFFFFF000000FFFFFFFFFFFF
      0202020202FFFFFFFFFFFF000000FF020202020202020202020202020202FF00
      0000FFFF02020202020202020202020202FFFF000000FFFFFF02020202020202
      02020202FFFFFF000000FFFFFFFF020202020202020202FFFFFFFF000000FFFF
      FFFFFF02020202020202FFFFFFFFFF000000FFFFFFFFFFFF0202020202FFFFFF
      FFFFFF000000FFFFFFFFFFFFFF020202FFFFFFFFFFFFFF000000FFFFFFFFFFFF
      FFFF02FFFFFFFFFFFFFFFF000000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF00
      0000}
  end
  object ButtonAngleDown: TBitBtn
    Left = 592
    Top = 192
    Width = 25
    Height = 33
    TabOrder = 2
    OnClick = ButtonAngleDownClick
    Glyph.Data = {
      9E050000424D9E05000000000000360400002800000011000000120000000100
      0800000000006801000000000000000000000001000000000000000000000000
      80000080000000808000800000008000800080800000C0C0C000C0DCC000F0CA
      A6000020400000206000002080000020A0000020C0000020E000004000000040
      20000040400000406000004080000040A0000040C0000040E000006000000060
      20000060400000606000006080000060A0000060C0000060E000008000000080
      20000080400000806000008080000080A0000080C0000080E00000A0000000A0
      200000A0400000A0600000A0800000A0A00000A0C00000A0E00000C0000000C0
      200000C0400000C0600000C0800000C0A00000C0C00000C0E00000E0000000E0
      200000E0400000E0600000E0800000E0A00000E0C00000E0E000400000004000
      20004000400040006000400080004000A0004000C0004000E000402000004020
      20004020400040206000402080004020A0004020C0004020E000404000004040
      20004040400040406000404080004040A0004040C0004040E000406000004060
      20004060400040606000406080004060A0004060C0004060E000408000004080
      20004080400040806000408080004080A0004080C0004080E00040A0000040A0
      200040A0400040A0600040A0800040A0A00040A0C00040A0E00040C0000040C0
      200040C0400040C0600040C0800040C0A00040C0C00040C0E00040E0000040E0
      200040E0400040E0600040E0800040E0A00040E0C00040E0E000800000008000
      20008000400080006000800080008000A0008000C0008000E000802000008020
      20008020400080206000802080008020A0008020C0008020E000804000008040
      20008040400080406000804080008040A0008040C0008040E000806000008060
      20008060400080606000806080008060A0008060C0008060E000808000008080
      20008080400080806000808080008080A0008080C0008080E00080A0000080A0
      200080A0400080A0600080A0800080A0A00080A0C00080A0E00080C0000080C0
      200080C0400080C0600080C0800080C0A00080C0C00080C0E00080E0000080E0
      200080E0400080E0600080E0800080E0A00080E0C00080E0E000C0000000C000
      2000C0004000C0006000C0008000C000A000C000C000C000E000C0200000C020
      2000C0204000C0206000C0208000C020A000C020C000C020E000C0400000C040
      2000C0404000C0406000C0408000C040A000C040C000C040E000C0600000C060
      2000C0604000C0606000C0608000C060A000C060C000C060E000C0800000C080
      2000C0804000C0806000C0808000C080A000C080C000C080E000C0A00000C0A0
      2000C0A04000C0A06000C0A08000C0A0A000C0A0C000C0A0E000C0C00000C0C0
      2000C0C04000C0C06000C0C08000C0C0A000F0FBFF00A4A0A000808080000000
      FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00FFFFFFFFFFFF
      FFFFFFFFFFFFFFFFFFFFFF000000FFFFFFFFFFFFFFFF02FFFFFFFFFFFFFFFF00
      0000FFFFFFFFFFFFFF020202FFFFFFFFFFFFFF000000FFFFFFFFFFFF02020202
      02FFFFFFFFFFFF000000FFFFFFFFFF02020202020202FFFFFFFFFF000000FFFF
      FFFF020202020202020202FFFFFFFF000000FFFFFF0202020202020202020202
      FFFFFF000000FFFF02020202020202020202020202FFFF000000FF0202020202
      02020202020202020202FF000000FFFFFFFFFFFF0202020202FFFFFFFFFFFF00
      0000FFFFFFFFFFFF0202020202FFFFFFFFFFFF000000FFFFFFFFFFFF02020202
      02FFFFFFFFFFFF000000FFFFFFFFFFFF0202020202FFFFFFFFFFFF000000FFFF
      FFFFFFFF0202020202FFFFFFFFFFFF000000FFFFFFFFFFFF0202020202FFFFFF
      FFFFFF000000FFFFFFFFFFFF0202020202FFFFFFFFFFFF000000FFFFFFFFFFFF
      0202020202FFFFFFFFFFFF000000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF00
      0000}
  end
end
