unit cadastro;

interface

uses
  Winapi.Windows, Winapi.Messages, System.SysUtils, System.Variants, System.Classes, Vcl.Graphics,
  Vcl.Controls, Vcl.Forms, Vcl.Dialogs, Vcl.StdCtrls, Vcl.Menus, Vcl.ComCtrls,
  Data.DB, Data.Win.ADODB, Data.FMTBcd, Data.SqlExpr, Vcl.ExtCtrls;

type
  TForm1 = class(TForm)
    menu: TPageControl;
    Armazenar: TTabSheet;
    Recuperar: TTabSheet;
    Configurar: TTabSheet;
    Label1: TLabel;
    Label2: TLabel;
    Label3: TLabel;
    CampoEndereco: TEdit;
    Button1: TButton;
    CampoInformacao: TMemo;
    Label4: TLabel;
    ADOConnection1: TADOConnection;
    QCadastrar: TADOQuery;
    DataSource1: TDataSource;
    Sobre: TTabSheet;
    Label5: TLabel;
    Label6: TLabel;
    Label7: TLabel;
    Servidor: TEdit;
    Usuario: TEdit;
    Senha: TEdit;
    Button4: TButton;
    Status: TLabel;
    Image1: TImage;
    ConsultaDadosCampo: TEdit;
    ConsultaInfoCampo: TEdit;
    Label9: TLabel;
    BotaoRecuperar: TButton;
    Label8: TLabel;
    StatusRecuperar: TLabel;
    procedure Button4Click(Sender: TObject);
    procedure Button1Click(Sender: TObject);
    procedure CampoEnderecoClick(Sender: TObject);
    procedure CampoInformacaoClick(Sender: TObject);
    procedure CampoEnderecoKeyPress(Sender: TObject; var Key: Char);
    procedure BotaoRecuperarClick(Sender: TObject);
    procedure ConsultaDadosCampoClick(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  Form1: TForm1;

implementation

{$R *.dfm}

procedure TForm1.Button1Click(Sender: TObject);
begin


  try

    QCadastrar.SQL.Text := 'insert into dbo.tbl_dados(id_numero, informacao)'+
    'values(:id_numero, :informacao)';
    QCadastrar.Parameters.ParamByName('id_numero').value := CampoEndereco.Text;
    QCadastrar.Parameters.ParamByName('informacao').value := CampoInformacao.Text;

    QCadastrar.ExecSQL;
    Status.Font.Color := clgreen;
    Status.Caption := 'Dados inseridos com sucesso !';
    CampoEndereco.Clear;
    CampoInformacao.Clear;

  Except

    Status.Font.Color := clred;
    Status.Caption := 'Erro ao inserir os dados !'

  end;



end;



procedure TForm1.BotaoRecuperarClick(Sender: TObject);
begin

  try

  Qcadastrar.SQL.Text := 'select informacao from dbo.tbl_dados where id_numero = :consulta';
  QCadastrar.Parameters.ParamByName('consulta').Value := ConsultaDadosCampo.Text;

  QCadastrar.Open;
  Qcadastrar.First;
  ConsultaInfoCampo.Text:= QCadastrar.FieldByName('informacao').AsString;


  Except

    StatusRecuperar.Font.Color := clred;

       StatusRecuperar.Caption := 'Não foi possível buscar os dados!';

  end;


end;



procedure TForm1.Button4Click(Sender: TObject);
begin


  try

      ADOConnection1.ConnectionString := 'Provider=SQLOLEDB.1;' +
      'qIntegrated Security=SSPI;' +
      'User ID=:Usuario;' +
      'Initial Catalog=db_cadastro;' +
      'Data Source=:ServidorCampo;' +
      'Workstation ID=:ServidorCampo;' +
      'password=":senha";';

      QCadastrar.Parameters.ParamByName('ServidorCampo').Value := Servidor.Text;
      QCadastrar.Parameters.ParamByName('Usuario').Value := Usuario.Text;
      QCadastrar.Parameters.ParamByName('senha').Value := Senha.Text;

      ADOConnection1.Connected := true;

      ShowMessage('Conectado com sucesso !');

  Except

      ShowMessage('Não foi possivel conectar ao banco !');

  end;



end;



procedure TForm1.CampoEnderecoClick(Sender: TObject);
begin

  CampoEndereco.Clear;
  Status.Caption := '';

end;



procedure TForm1.CampoEnderecoKeyPress(Sender: TObject; var Key: Char);
begin

  if (key in ['0'..'9'] = false) then
  begin
       ShowMessage('Somente números');
       CampoEndereco.Clear;
  end;

 end;

procedure TForm1.CampoInformacaoClick(Sender: TObject);
begin

  CampoInformacao.Clear;

end;

procedure TForm1.ConsultaDadosCampoClick(Sender: TObject);
begin

  ConsultaDadosCampo.Clear;

end;

end.




