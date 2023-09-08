object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'Cadastro'
  ClientHeight = 341
  ClientWidth = 470
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -17
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 21
  object menu: TPageControl
    Left = 0
    Top = -2
    Width = 473
    Height = 345
    ActivePage = Armazenar
    TabOrder = 0
    object Armazenar: TTabSheet
      Caption = 'Armazenar'
      object Label1: TLabel
        Left = 36
        Top = 67
        Width = 69
        Height = 18
        Caption = 'Endere'#231'o'
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -15
        Font.Name = 'Verdana'
        Font.Style = []
        ParentFont = False
      end
      object Label2: TLabel
        Left = 36
        Top = 119
        Width = 86
        Height = 18
        Caption = 'Informa'#231#227'o'
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -15
        Font.Name = 'Verdana'
        Font.Style = []
        ParentFont = False
      end
      object Label3: TLabel
        Left = 14
        Top = 22
        Width = 123
        Height = 31
        Caption = 'Cadastrar'
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -25
        Font.Name = 'Verdana'
        Font.Style = []
        ParentFont = False
      end
      object Status: TLabel
        Left = 168
        Top = 225
        Width = 5
        Height = 21
        Color = clLime
        ParentColor = False
      end
      object CampoEndereco: TEdit
        Left = 36
        Top = 91
        Width = 145
        Height = 22
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = 'Verdana'
        Font.Style = []
        ParentFont = False
        TabOrder = 0
        Text = 'N'#176
        OnClick = CampoEnderecoClick
        OnKeyPress = CampoEnderecoKeyPress
      end
      object Button1: TButton
        Left = 36
        Top = 220
        Width = 105
        Height = 33
        Caption = 'Salvar'
        TabOrder = 1
        OnClick = Button1Click
      end
      object CampoInformacao: TMemo
        Left = 36
        Top = 143
        Width = 245
        Height = 71
        Lines.Strings = (
          '....')
        TabOrder = 2
        OnClick = CampoInformacaoClick
      end
    end
    object Recuperar: TTabSheet
      Caption = 'Recuperar'
      ImageIndex = 1
      object Label4: TLabel
        Left = 16
        Top = 11
        Width = 192
        Height = 31
        Caption = 'Consulta dados'
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -25
        Font.Name = 'Verdana'
        Font.Style = []
        ParentFont = False
      end
      object Label9: TLabel
        Left = 32
        Top = 160
        Width = 92
        Height = 21
        Caption = 'Informa'#231#245'es'
      end
      object Label8: TLabel
        Left = 32
        Top = 48
        Width = 69
        Height = 18
        Caption = 'Endere'#231'o'
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -15
        Font.Name = 'Verdana'
        Font.Style = []
        ParentFont = False
      end
      object StatusRecuperar: TLabel
        Left = 32
        Top = 232
        Width = 5
        Height = 21
      end
      object ConsultaDadosCampo: TEdit
        Left = 32
        Top = 70
        Width = 241
        Height = 29
        TabOrder = 0
        Text = 'N'#176
        OnClick = ConsultaDadosCampoClick
      end
      object ConsultaInfoCampo: TEdit
        Left = 32
        Top = 187
        Width = 241
        Height = 29
        TabOrder = 1
        Text = '...'
      end
      object BotaoRecuperar: TButton
        Left = 32
        Top = 105
        Width = 129
        Height = 33
        Caption = 'Recuperar'
        TabOrder = 2
        OnClick = BotaoRecuperarClick
      end
    end
    object Configurar: TTabSheet
      Caption = 'Configurar'
      ImageIndex = 3
      object Label5: TLabel
        Left = 16
        Top = 48
        Width = 60
        Height = 21
        Caption = 'Servidor'
      end
      object Label6: TLabel
        Left = 160
        Top = 120
        Width = 45
        Height = 21
        Caption = 'Senha'
      end
      object Label7: TLabel
        Left = 16
        Top = 120
        Width = 56
        Height = 21
        Caption = 'Usu'#225'rio'
      end
      object Servidor: TEdit
        Left = 16
        Top = 75
        Width = 121
        Height = 29
        TabOrder = 0
      end
      object Usuario: TEdit
        Left = 16
        Top = 147
        Width = 121
        Height = 29
        TabOrder = 1
      end
      object Senha: TEdit
        Left = 160
        Top = 147
        Width = 121
        Height = 29
        TabOrder = 2
      end
      object Button4: TButton
        Left = 16
        Top = 200
        Width = 117
        Height = 49
        Caption = 'Conectar'
        TabOrder = 3
        OnClick = Button4Click
      end
    end
    object Sobre: TTabSheet
      Caption = 'Sobre'
      ImageIndex = 3
      object Image1: TImage
        Left = 168
        Top = 48
        Width = 105
        Height = 105
      end
    end
  end
  object ADOConnection1: TADOConnection
    ConnectionString = 
      'Provider=SQLOLEDB.1;Persist Security Info=False;User ID=sa;Initi' +
      'al Catalog=tbl_dados;Data Source=localhost\KAPTUREALL'
    Provider = 'SQLOLEDB.1'
    Left = 380
    Top = 270
  end
  object QCadastrar: TADOQuery
    Connection = ADOConnection1
    Parameters = <>
    SQL.Strings = (
      'select * from tbl_cadastro;')
    Left = 340
    Top = 182
  end
  object DataSource1: TDataSource
    DataSet = QCadastrar
    Left = 364
    Top = 110
  end
end
