/*
********************************************************************************************************
File: ACCESS-RID
   Microprocessor: ATMel/Arduino Uno/Arduino Mega and its variants
   Language: Wiring/C
   Purpose: Enter a certain password to grant access

   Operation: When turning on, read the lock sensor status, found on the door;
            if the sensor is giving continuity and if the user has not typed a;
           correct password the alarm sounds until the user enters the correct password, if the
           password is incorrect send password data to client via network or location
           and the time of the incident. If the password is correct, the green led will light up, releasing
           access and data via the network.

   Author: Marco Silva
   Date: 02/15/2018
   Location: Bento Ferreira - ES

********************************************************************************************************
  Este codigo estará disponivel ao domínio público.
*/

// The display messages will be added if the operator wants to add them to the project architecture
// including libraries
#include <Wire.h>
#include <SPI.h>
#include <Ethernet.h>
#define WEBARDUINO_AUTH_REALM "Developer to Project based to System RID, by Marcos Silva"
#include <Keypad.h>
//#include <LiquidCrystal_I2C.h>
#include <LiquidCrystal.h>
#include <WebServer.h>
//Defining boolean variable

boolean tog1 = false;
boolean tog2 = true;

//Arduino MEGA Shield MAC
/* CHANGE THIS IF MAC IS EQUAL TO ANY ORIGINAL VALUE. The MAC number must be
     different from any other device on the network or you will have
     Problems receiving packages. */

static uint8_t mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xBA, 0xED }; //MAC da Shield

/* CHANGE THIS TO SHARING YOUR HOST NETWORK. Most home networks are on
   the 192.168.0.XXX or 192.168.1.XXX subrange. choose an address
   This is not in use and will not be automatically allocated by
   DHCP from your router. */

static uint8_t ip[] = { 192, 168, 200, 150 }; // Numero de IP (teste)

#define PREFIX ""
WebServer webserver(PREFIX, 80); // HTTP service prefix

////////////////////////////
void defaultCmd(WebServer &server, WebServer::ConnectionType type, char *, bool)
{
  server.httpSuccess();
  if (type != WebServer::HEAD)
  {
    P(corpo) = ("<!--\n"
                "Author: Marcos Silva\n"
                "Author URL: http://aragones.esy.es\n"
                "License: Creative Commons Attribution 3.0 Unported\n"
                "License URL: http://creativecommons.org/licenses/by/3.0/\n"
                "-->\n"
                "<!DOCTYPE HTML>\n"
                "<HTML><HEAD><TITLE>Entrar</TITLE>\n"
                "<meta name='viewport' content='width=device-width, initial-scale=1'>\n"
                "<meta http-equiv='Content-Type' content='text/html; charset=utf-8'/>\n"
                "<meta name='keywords' content='Sistema de exemplo para erro de login e senha por Marcos Silva'/>\n"
                "<script type='application/x-javascript'> addEventListener('load', function() { setTimeout(hideURLbar, 0); }, false); function hideURLbar(){ window.scrollTo(0,1); } </script>"
                "<!-- bootstrap-css -->"
                "<link rel='stylesheet' href='http://cdn.rawgit.com/aragonxpd154/libs/master/bootstrap.min.css'>"
                "<!-- //bootstrap-css -->"
                "<!-- Custom CSS -->"
                "<link href='http://cdn.rawgit.com/aragonxpd154/libs/master/images/style.css' rel='stylesheet' type='text/css'/>"
                "<link href='http://cdn.rawgit.com/aragonxpd154/libs/master/style-responsive.css' rel='stylesheet'/>"
                "<!-- font CSS -->"
                "<link href='http://fonts.googleapis.com/css?family=Roboto:400,100,100italic,300,300italic,400italic,500,500italic,700,700italic,900,900italic' rel='stylesheet' type='text/css'>"
                "<!-- font-awesome icons -->"
                "<link rel='stylesheet' href='https://cdn.rawgit.com/aragonxpd154/libs/master/font.css' type='text/css'/>"
                "<link href='http://cdn.rawgit.com/aragonxpd154/libs/master/font-awesome.css' rel='stylesheet'>"
                "<!-- //font-awesome icons -->"
                "<script src='http://cdn.rawgit.com/aragonxpd154/libs/master/jquery2.0.3.min.js'></script>"
                "</head>"
                "<body>"
                "<!--main content start-->"
                "<div class='eror-w3'>"
                "<div class='agile-info'>"
                "<h3>ACESSAR O</h3>"
                "<h2>RID</h2>"
                "<p>Acesse o ambiente seguro RID</p>"
                "<a href='/private.html'>ENTRAR</a>"
                "</div>"
                "</div>"
                "<script src='http://cdn.rawgit.com/aragonxpd154/libs/master/bootstrap.js'></script>"
                "<script src='http://cdn.rawgit.com/aragonxpd154/libs/master/jquery.dcjqaccordion.2.7.js'></script>"
                "<script src='https://cdn.rawgit.com/aragonxpd154/libs/master/scripts.js'></script>"
                "<script src='https://cdn.rawgit.com/aragonxpd154/libs/master/jquery.slimscroll.js'></script>"
                "<script src='https://cdn.rawgit.com/aragonxpd154/libs/master/jquery.nicescroll.js'></script>"
                "<!--[if lte IE 8]><script language='javascript' type='text/javascript' src='js/flot-chart/excanvas.min.js'></script><![endif]-->"
                "<script src='https://cdn.rawgit.com/aragonxpd154/libs/master/jquery.scrollTo.js'></script>"
                "</body>"
                "</html>");

    server.printP(corpo);
  }

}
/////////////////////////////////////////////////////////
void privateCmd(WebServer &server, WebServer::ConnectionType type, char *, bool)
{
  /* if the user has requested this page using the following credentials
     username = user
     password = user
     display a page saying "Hello User"

     the credentials have to be concatenated with a colon like
     username:password
     and encoded using Base64 - this should be done outside of your Arduino
     to be easy on your resources

     in other words: "dXNlcjp1c2Vy" is the Base64 representation of "user:user"

     if you need to change the username/password dynamically please search
     the web for a Base64 library */
  if (server.checkCredentials("dXNlcjp1c2Vy"))
  {
    server.httpSuccess();
    if (type != WebServer::HEAD)
    {
      P(corpoHTMLSys) = ("<!--System developer by: Marcos Silva (aragones xpd154)\n"
                         "Author: Marcos Silva etc..\n"
                         "Author URL: http://aragones.esy.es\n"
                         "License: Creative Commons Attribution 3.0 Unported\n"
                         "License URL: http://creativecommons.org/licenses/by/3.0/\n"
                         "-->\n"
                         "<!DOCTYPE HTML>\n"
                         "<head>\n"
                         "<meta http-equiv='refresh' content='5';url=http://192.168.0.106>\n"
                         "<title>Painel de Administração</title>\n"
                         "<meta name='viewport' content='width=device-width, initial-scale=1'>\n"
                         "<meta http-equiv='Content-Type' content='text/html; charset=utf-8' />\n"
                         "<meta name='keywords' content='Painel de Controle de Luz' />\n"
                         "<script type='application/x-javascript'> addEventListener('load', function() { setTimeout(hideURLbar, 0); }, false); function hideURLbar(){ window.scrollTo(0,1); } </script>\n"
                         "<!-- bootstrap-css -->\n"
                         "<link href='https://maxcdn.bootstrapcdn.com/bootstrap/3.3.1/css/bootstrap.min.css' rel='stylesheet'></link>\n"
                         "<link rel='stylesheet' href='https://cdn.rawgit.com/aragonxpd154/rid-pro/master/css/bootstrap.min.css'>\n"
                         "<!-- //bootstrap-css -->\n"
                         "<!-- Custom CSS -->\n"
                         "<link href='https://cdn.rawgit.com/aragonxpd154/rid-pro/master/css/style.css' rel='stylesheet' type='text/css' />\n"
                         "<link href='https://cdn.rawgit.com/aragonxpd154/rid-pro/master/css/style-responsive.css' rel='stylesheet'/>\n"
                         "<!-- font CSS -->\n"
                         "<link href='http://fonts.googleapis.com/css?family=Roboto:400,100,100italic,300,300italic,400italic,500,500italic,700,700italic,900,900italic' rel='stylesheet' type='text/css'>\n"
                         "<!-- font-awesome icons -->\n"
                         "<link rel='stylesheet' href='https://cdn.rawgit.com/aragonxpd154/rid-pro/master/css/font.css' type='text/css'/>\n"
                         "<link href='https://cdn.rawgit.com/aragonxpd154/rid-pro/master/css/font-awesome.css' rel='stylesheet'>\n"
                         "<link rel='stylesheet' href='https://cdn.rawgit.com/aragonxpd154/rid-pro/master/css/morris.css' type='text/css'/>\n"
                         "<!-- calendar -->\n"
                         "<link rel='stylesheet' href='https://cdn.rawgit.com/aragonxpd154/rid-pro/master/css/monthly.css'>\n"
                         "<!-- //calendar -->\n"
                         "<!-- //font-awesome icons -->\n"
                         "<script src='https://cdn.rawgit.com/aragonxpd154/rid-pro/master/js/jquery2.0.3.min.js'></script>\n"
                         "<script src='https://cdn.rawgit.com/aragonxpd154/rid-pro/master/js/raphael-min.js'></script>\n"
                         "<script src='https://cdn.rawgit.com/aragonxpd154/rid-pro/master/js/morris.js'></script>\n"
                         "</head>\n"
                         "<body>\n"
                         "<section id='container'>\n"
                         "<!--header start-->\n"
                         "<header class='header fixed-top clearfix'>\n"
                         "<!--logo start-->\n"
                         "<div class='brand'>\n"
                         "<a href='index.html' class='logo'>\n"
                         "rid\n"
                         "</a>\n"
                         "<div class='sidebar-toggle-box'>\n"
                         "<div class='fa fa-bars'></div>\n"
                         "</div>\n"
                         "</div>\n"
                         "<!--logo end-->\n"
                         "<div class='nav notify-row' id='top_menu'>\n"
                         "<!--  notification start -->\n"
                         "<ul class='nav top-menu'>\n"
                         "<!-- settings start -->\n"
                         "<li class='dropdown'>\n"
                         "<a data-toggle='dropdown' class='dropdown-toggle' href='#'>\n"
                         "<i class='fa fa-tasks'></i>\n"
                         "<span class='badge bg-success'>1</span>\n"
                         "</a>\n"
                         "<ul class='dropdown-menu extended tasks-bar'>\n"
                         "<li>\n"
                         "<p class=''>Controle</p>\n"
                         "</li>\n"
                         "<li>\n"
                         "</li>\n"
                         "<li>\n"
                         "</li>\n"
                         "<li>\n"
                         "</li>\n"
                         "<li>\n"
                         "<a href='#'>\n"
                         " </a>\n"
                         "</li>\n"
                         "<li class='external'>\n"
                         "<a href='#'>Ver todos os controles</a>\n"
                         "</li>\n"
                         "</ul>\n"
                         "</li>\n"
                         "<!-- settings end -->\n"
                         "<!-- inbox dropdown start-->\n"
                         "<li id='header_inbox_bar' class='dropdown'>\n"
                         "<a data-toggle='dropdown' class='dropdown-toggle' href='#'>\n"
                         "<i class='fa fa-envelope-o'></i>\n"
                         "<span class='badge bg-important'>0</span>\n"
                         "</a>\n"
                         "<ul class='dropdown-menu extended inbox'>\n"
                         "<li>\n"
                         "<p class='red'>E-mail</p>\n"
                         "</li>\n"
                         "<li>\n"
                         "</li>\n"
                         "<li>\n"
                         "</li>\n"
                         "<li>\n"
                         "</li>\n"
                         "<li>\n"
                         "</li>\n"
                         "<li>\n"
                         "<a href='#'>Ver todas as mensagens</a>\n"
                         "</li>\n"
                         "</ul>\n"
                         "</li>\n"
                         "<!-- inbox dropdown end -->\n"
                         "<!-- notification dropdown start-->\n"
                         "<li id='header_notification_bar' class='dropdown'>\n"
                         "<a data-toggle='dropdown' class='dropdown-toggle' href='#'>\n\n"
                         "<i class='fa fa-bell-o'></i>\n"
                         "<span class='badge bg-warning'>0</span>\n"
                         "</a>\n"
                         "<ul class='dropdown-menu extended notification'>\n"
                         "<!-- <li>\n"
                         "<p>Notificações</p>\n"
                         "</li>\n"
                         "<li>\n"
                         "<div class='alert alert-info clearfix'>\n"
                         "<span class='alert-icon'><i class='fa fa-bolt'></i></span>\n"
                         "<div class='noti-info'>\n"
                         "<a href='#'> .</a>\n"
                         "</div>\n"
                         "</div>\n"
                         "</li>\n"
                         "<li>\n"
                         "<div class='alert alert-danger clearfix'>\n"
                         "<span class='alert-icon'><i class='fa fa-bolt'></i></span>\n"
                         "<div class='noti-info'>\n"
                         "<a href='#'> </a>\n"
                         "</div>\n"
                         "</div>\n"
                         "</li>\n"
                         "<li>\n"
                         "<div class='alert alert-success clearfix'>\n"
                         "<span class='alert-icon'><i class='fa fa-bolt'></i></span>\n"
                         "<div class='noti-info'>\n"
                         "<a href='#'> </a>\n"
                         "</div>\n"
                         "</div>\n"
                         "</li>\n"
                         "</ul>\n"
                         "</li> -->\n"
                         "<!-- notification dropdown end -->\n"
                         "</ul>\n"
                         "<!--  notification end -->\n"
                         "</div>\n"
                         "<div class='top-nav clearfix'>\n"
                         "<!--search & user info start-->\n"
                         "<ul class='nav pull-right top-menu'>\n"
                         "<li>\n"
                         "<input type='text' class='form-control search' placeholder=' Pesquisar'>\n"
                         "</li>\n"
                         "<!-- user login dropdown start-->\n"
                         "<li class='dropdown'>\n"
                         "<a data-toggle='dropdown' class='dropdown-toggle' href='#'>\n"
                         "<img alt='' src='https://i.imgur.com/izukq95.png'\n>"
                         "<span class='username'>Administrador</span>\n"
                         "<b class='caret'></b>\n"
                         "</a>\n"
                         "<ul class='dropdown-menu extended logout'>\n"
                         "<li><a href='#'><i class=' fa fa-suitcase'></i>Perfil</a></li>\n"
                         "<li><a href='#'><i class='fa fa-cog'></i> Configurações</a></li>\n"
                         "<li><a href='login.html'><i class='fa fa-key'></i> Sair</a></li>\n"
                         "</ul>\n"
                         "</li>\n"
                         "<!-- user login dropdown end -->\n"

                         "</ul>\n"
                         "<!--search & user info end-->\n"
                         "</div>\n"
                         "</header>\n"
                         "<!--header end-->\n"
                         "<!--sidebar start-->\n"
                         "<aside>\n"
                         "<div id='sidebar' class='nav-collapse'>\n"
                         "<!-- sidebar menu start-->\n"
                         "<div class='leftside-navigation'>\n"
                         "<ul class='sidebar-menu' id='nav-accordion'>\n"
                         "<li>\n"
                         "<a class='active' href='index.html'>\n"
                         "<i class='fa fa-dashboard'></i>\n"
                         "<span>Painel de Controle</span>\n"
                         "</a>\n"
                         "</li>\n"

                         "<li class='sub-menu'>\n"
                         "<a href='javascript:;'>\n"
                         "<i class='fa fa-book'></i>\n"
                         "<span>Automação</span>\n"
                         "</a>\n"
                         "<ul class='sub'>\n"
                         "<li><a href='typography.html'>Luz</a></li>\n"
                         "<li><a href='glyphicon.html'>Temperatura</a></li>\n"

                         "</ul>\n"
                         "</li>\n"
                         "<li class='sub-menu'>\n"
                         "<a href='javascript:;'>\n"
                         "<i class='fa fa-th'></i>\n"
                         "<span>Tabelas de Configurações</span>\n"
                         "</a>\n"
                         "<ul class='sub'>\n"
                         "<li><a href='basic_table.html'>Modo Basico</a></li>\n"
                         "<li><a href='responsive_table.html'>Modo avançado</a></li>\n"
                         "</ul>\n"
                         "</li>\n"
                         "<li class='sub-menu'>\n"
                         "<a href='javascript:;'>\n"
                         "<i class=' fa fa-bar-chart-o'></i>\n"
                         "<span>Gráficos</span>\n"
                         "</a>\n"
                         "<ul class='sub'>\n"
                         "<li><a href='chartjs.html'>Temperatura</a></li>\n"
                         "<li><a href='flot_chart.html'>Tensão</a></li>\n"
                         "</ul>\n"
                         "</li>\n"


                         "<li>\n"
                         "<a href='login.html'>\n"
                         "<i class='fa fa-user'></i>\n"
                         "<span>Sair</span>\n"
                         "</a>\n"
                         "</li>\n"
                         "</ul>            </div>\n"
                         "<!-- sidebar menu end-->\n"
                         "</div>\n"
                         "</aside>\n"
                         "<!--sidebar end-->\n"
                         "<!--main content start-->\n"
                         "<section id='main-content'>\n"
                         "<section class='wrapper'>\n"
                         "<!-- //market-->\n"
                         "<div class='market-updates'>\n"
                         "<div class='col-md-3 market-update-gd'>\n"
                         "<div class='market-update-block clr-block-2'>\n"
                         "<div class='col-md-4 market-update-right'>\n"
                         "<i class=''> </i>\n"
                         "</div>\n"
                         "<div class='col-md-8 market-update-left'>\n"
                         "<h4>Tensão</h4>\n"
                         "<h3>???\n"


                         "</h3>\n"
                         "<p></p>\n"
                         "</div>\n"
                         "<div class='clearfix'> </div>\n"
                         "</div>\n"
                         "</div>\n"
                         "<div class='col-md-3 market-update-gd'>\n"
                         "<div class='market-update-block clr-block-1'>\n"
                         "<div class='col-md-4 market-update-right'>\n"
                         "<i class='' ></i>\n"
                         "</div>\n"
                         "<div class='col-md-8 market-update-left'>\n"
                         "<h4>Chaveamento</h4>\n"
                         "<h3>Manual</h3>\n"
                         "<p></p>\n"
                         "</div>\n"
                         "<div class='clearfix'> </div>\n"
                         "</div>\n"
                         "</div>\n"
                         "<div class='col-md-3 market-update-gd'>\n"
                         "<div class='market-update-block clr-block-3'>\n"
                         "<div class='col-md-4 market-update-right'>\n"
                         "<i class=''></i>\n"
                         "</div>\n"
                         "<div class='col-md-8 market-update-left'>\n"
                         "<h4>Temperatura</h4>\n"
                         "<h3>?? Cº</h3>\n"
                         "<p></p>\n"
                         "</div>\n"
                         "<div class='clearfix'> </div>\n"
                         "</div>\n"
                         "</div>\n"
                         "<div class='col-md-3 market-update-gd'>\n"
                         "<div class='market-update-block clr-block-4'>\n"
                         "<div class='col-md-4 market-update-right'>\n"
                         "<i class='' aria-hidden='true'></i>\n"
                         "</div>\n"
                         "<div class='col-md-8 market-update-left'>\n"
                         "<h4>Analisador</h4>\n"
                         "<h3>???</h3>\n"
                         "<p></p>\n"
                         "</div>\n"
                         "<div class='clearfix'> </div>\n"
                         "</div>\n"
                         "</div>\n"
                         "<div class='clearfix'> </div>\n"
                         "</div>  \n"
                         "<!-- //market-->\n"
                         "<div class='row'>\n"
                         "<div class='panel-body'>\n"
                         "<div class='col-md-12 w3ls-graph'>\n"
                         "<!--agileinfo-grap-->\n"
                         "<div class='agileinfo-grap'>\n"
                         "<div class='agileits-box'>\n"
                         "<header class='agileits-box-header clearfix'>\n"
                         "<h3>Gráfico de Tensão</h3>\n"
                         "<div class='toolbar'>\n"


                         "</div>\n"
                         "</header>\n"
                         "<div class='agileits-box-body clearfix'>\n"
                         "<div id='hero-area'></div>\n"
                         "</div>\n"
                         "</div>\n"
                         "</div>\n"
                         "<!--//agileinfo-grap-->\n"

                         "</div>\n"
                         "</div>\n"
                         "</div>\n"

                         "<!-- //market-->\n"
                         "<div class='row'>\n"
                         "<div class='panel-body'>\n"
                         "<div class='col-md-12 w3ls-graph'>\n"
                         "<!--agileinfo-grap-->\n"
                         "<div class='agileinfo-grap'>\n"
                         "<div class='agileits-box'>\n"
                         "<header class='agileits-box-header clearfix'>\n"
                         "<h3>Interface de Controle</h3>\n"
                         "<div class='toolbar'>\n"
                         "<div class='jumbotron'>\n"
                         "<div class='row'>\n"
                         "<div class='col-md-10'>\n"
                         "<table class='table table-bordered'>\n"
                         "<tbody>\n"
                         "<div class='row'>\n"
                         "<div class='col-md-10'>\n"
                         "<table class='table table-bordered'>\n"
                         "<tbody>\n");



      P(S1On) = ("fthfhdst");

      P(S1Off) = ("kiodon");


      P(corpoHTMLSys1) = ("<tr><td width=130px>Lampada 1  - \n"
                          "Ligado\n"
                          "</td><td>\n"
                          "<a class='btn btn-danger btn-lg' href='?S1Desligado'>Desligar</buttLigado>\n"
                          "</td></tr>\n"
                          "<tr><td width=130px>Lampada 2 - \n"
                          "Desligado\n"
                          "</td><td>\n"
                          "<a class='btn btn-success btn-lg' href='?S2Ligado'>Ligar</buttLigado>\n"
                          "</td></tr>\n"
                          "<tr><td width=130px>Lampada 2 - \n"
                          "Desligado\n"
                          "</b></td><td>\n"
                          "<a class='btn btn-success btn-lg' href='?S3Ligado'>Ligar</buttLigado>\n"
                          "</td></tr>\n"
                          "<tr><td width=130px>Lampada 2 - \n"
                          "Desligado\n"
                          "</td><td>\n"
                          "<a class='btn btn-success btn-lg' href='?S4Ligado'>Ligar</buttLigado>\n"
                          "</td></tr>\n"
                          "<tr><td>RGB</td><td>\n"
                          "<a class='btn btn-primary btn-lg' href='?blue' >Azul</a>&nbsp;\n"
                          "<a class='btn btn-danger btn-lg' href='?red' >Vermelho</a>&nbsp;\n"
                          "<a class='btn btn-success btn-lg' href='?green' >Verde</a>&nbsp;\n"
                          "<a class='btn btn-default btn-lg' href='?white' >Branco</a>&nbsp;\n"
                          "<a class='btn btn-link' href='?rgboff' >Desligar</a>&nbsp;\n"
                          "</td></tr>\n"
                          "<tr><td colspan=2>Chave 1 - \n"
                          "<span class='glyphicon glyphicon-ban-circle' aria-hidden='true'></span>\n"
                          "<br>\n"
                          "Chave 2 - \n"
                          "<span class='glyphicon glyphicon-ban-circle' aria-hidden='true'></span>\n"
                          "<br>\n"
                          "Chave 3 - \n"
                          "<span class='glyphicon glyphicon-ban-circle' aria-hidden='true'></span>\n"
                          "<br>\n"
                          "<a class='btn btn-link' href='/'>Verificar status chaves</a>\n"
                          "</td></tr>\n"
                          "</tbody>\n"
                          "</table>   \n"

                         );

      P(corpoHTMLSys2) = (
                           "</div>\n"
                           "</header>\n"
                           "<div class='agileits-box-body clearfix'>\n"
                           "<div id='hero-area'></div>\n"
                           "</div>\n"
                           "</div>\n"
                           "</div>\n"
                           "<!--//agileinfo-grap-->\n"

                           "</div>\n"
                           "</div>\n"
                           "</div>\n"

                           "<div class='agil-info-calendar'>\n"
                           "<!-- calendar -->\n"
                           "<div class='col-md-6 agile-calendar'>\n"
                           "<div class='calendar-widget'>\n"
                           "<div class='panel-heading ui-sortable-handle'>\n"
                           "<span class='panel-icon'>\n"
                           "<i class='fa fa-calendar-o'></i>\n"
                           "</span>\n"
                           "<span class='panel-title'> Calendário de ação</span>\n"
                           "</div>\n"
                           "<!-- grids -->\n"
                           "<div class='agile-calendar-grid'>\n"
                           "<div class='page'>\n"

                           "<div class='w3l-calendar-left'>\n"
                           "<div class='calendar-heading'>\n"

                           "</div>\n"
                           "<div class='monthly' id='mycalendar'></div>\n"
                           "</div>\n"

                           "<div class='clearfix'> </div>\n"
                           "</div>\n"
                           "</div>\n"
                           "</div>\n"
                           "</div>\n"
                           "<!-- //calendar -->\n"
                           "<div class='col-md-6 w3agile-notifications'>\n"
                           "<div class='notifications'>\n"
                           "<!--notification start-->\n"

                           "<header class='panel-heading'>\n"
                           "Notificações \n"
                           "</header>\n"
                           "<div class='notify-w3ls'>\n"


                           "</div>\n"

                           "<!--notification end-->\n"
                           "</div>\n"
                           "</div>\n"
                           "<div class='clearfix'> </div>\n"
                           "</div>\n"
                           "<!-- tasks -->\n"
                           "<!-- <div class='agile-last-grids'>\n"

                           "<div class='col-md-4 agile-last-left'>\n"
                           "<div class='agile-last-grid'>\n"
                           "<div class='area-grids-heading'>\n"
                           "<h3>Monthly</h3>\n"
                           "</div>\n"
                           "<div id='graph7'></div>\n"
                           "<script>\n"
                           "// This crosses a DST boundary in the UK.\n"
                           "Morris.Area({\n"
                           "element: 'graph7',\n"
                           "data: [\n"
                           "{x: '2013-03-30 22:00:00', y: 3, z: 3},\n"
                           "{x: '2013-03-31 00:00:00', y: 2, z: 0},\n"
                           "{x: '2013-03-31 02:00:00', y: 0, z: 2},\n"
                           "{x: '2013-03-31 04:00:00', y: 4, z: 4}\n"
                           "],\n"
                           "xkey: 'x',\n"
                           "ykeys: ['y', 'z'],\n"
                           "labels: ['Y', 'Z']\n"
                           "});\n"
                           "</script>\n"

                           "</div>\n"
                           "</div>\n"
                           "<div class='col-md-4 agile-last-left agile-last-middle'>\n"
                           "<div class='agile-last-grid'>\n"
                           "<div class='area-grids-heading'>\n"
                           "<h3>Daily</h3>\n"
                           "</div>\n"
                           "<div id='graph8'></div>\n"
                           "<script>\n"
                           "/* data stolen from http://howmanyleft.co.uk/vehicle/jaguar_'e'_type */\n"
                           "var day_data = [\n"
                           "{'period': '2016-10-01', 'licensed': 3407, 'sorned': 660},\n"
                           "{'period': '2016-09-30', 'licensed': 3351, 'sorned': 629},\n"
                           "{'period': '2016-09-29', 'licensed': 3269, 'sorned': 618},\n"
                           "{'period': '2016-09-20', 'licensed': 3246, 'sorned': 661},\n"
                           "{'period': '2016-09-19', 'licensed': 3257, 'sorned': 667},\n"
                           "{'period': '2016-09-18', 'licensed': 3248, 'sorned': 627},\n"
                           "{'period': '2016-09-17', 'licensed': 3171, 'sorned': 660},\n"
                           "{'period': '2016-09-16', 'licensed': 3171, 'sorned': 676},\n"
                           "{'period': '2016-09-15', 'licensed': 3201, 'sorned': 656},\n"
                           "{'period': '2016-09-10', 'licensed': 3215, 'sorned': 622}\n"
                           "];\n"
                           "Morris.Bar({\n"
                           "element: 'graph8',\n"
                           "data: day_data,\n"
                           "xkey: 'period',\n"
                           "ykeys: ['licensed', 'sorned'],\n"
                           "labels: ['Licensed', 'SORN'],\n"
                           "xLabelAngle: 60\n"
                           "});\n"
                           "</script>\n"
                           "</div>\n"
                           "</div>\n"
                           "<div class='col-md-4 agile-last-left agile-last-right'>\n"
                           "<div class='agile-last-grid'>\n"
                           "<div class='area-grids-heading'>\n"
                           "<h3>Yearly</h3>\n"
                           "</div>\n"
                           "<div id='graph9'></div>\n"
                           "<script>\n"
                           "var day_data = [\n"
                           "{'elapsed': 'I', 'value': 34},\n"
                           "{'elapsed': 'II', 'value': 24},\n"
                           "{'elapsed': 'III', 'value': 3},\n"
                           "{'elapsed': 'IV', 'value': 12},\n"
                           "{'elapsed': 'V', 'value': 13},\n"
                           "{'elapsed': 'VI', 'value': 22},\n"
                           "{'elapsed': 'VII', 'value': 5},\n"
                           "{'elapsed': 'VIII', 'value': 26},\n"
                           "{'elapsed': 'IX', 'value': 12},\n"
                           "{'elapsed': 'X', 'value': 19}\n"
                           "];\n"
                           "Morris.Line({\n"
                           "element: 'graph9',\n"
                           "data: day_data,\n"
                           "xkey: 'elapsed',\n"
                           "ykeys: ['value'],\n"
                           "labels: ['value'],\n"
                           "parseTime: false\n"
                           "});\n"
                           "</script>\n"


                           "</body>\n"
                           "</html>\n" );

      P(corpoHTMLSys3) = ( "</div>\n"
                           "</div>\n"
                           "<div class='clearfix'> </div>\n"
                           "</div>\n"
                           "<!-- //tasks -->\n"
                           "<div class='agileits-w3layouts-stats'>\n"

                           "<div class='col-md-8 stats-info stats-last widget-shadow'>\n"

                           "</section>\n"
                           "<!-- footer -->\n"
                           "<div class='footer'>\n"
                           "<div class='wthree-copyright'>\n"
                           "<p>© 2017  RID. All rights reserved | Todos os direitos reservados <a href='http://aragones.esy.es'>Zutup Softwares e Aragones Projetos</a></p>\n"
                           "</div>\n"
                           "</div>\n"
                           "<!-- / footer -->\n"
                           "</section>\n"
                           "<!--main content end-->\n"
                           "</section>\n"
                           "<script src='https://cdn.rawgit.com/aragonxpd154/rid-pro/master/js/bootstrap.js'></script>\n"
                           "<script src='https://cdn.rawgit.com/aragonxpd154/rid-pro/master/js/jquery.dcjqaccordion.2.7.js'></script>\n"
                           "<script src='https://cdn.rawgit.com/aragonxpd154/rid-pro/master/js/scripts.js'></script>\n"
                           "<script src='https://cdn.rawgit.com/aragonxpd154/rid-pro/master/js/jquery.slimscroll.js'></script>\n"
                           "<script src='https://cdn.rawgit.com/aragonxpd154/rid-pro/master/js/jquery.nicescroll.js'></script>\n"
                           "<!--[if lte IE 8]><script language='javascript' type='text/javascript' src='js/flot-chart/excanvas.min.js'></script><![endif]-->\n"
                           "<script src='https://cdn.rawgit.com/aragonxpd154/rid-pro/master/js/jquery.scrollTo.js'></script>\n"
                           "<!-- morris JavaScript -->  \n");

      P(corpoHTMLSys4) = ("<script>\n"
                          "$(document).ready(function() {\n"
                          "//BOX BUTTON SHOW AND CLOSE Grafico de Tensão\n"
                          "jQuery('.small-graph-box').hover(function() {\n"
                          "jQuery(this).find('.box-button').fadeIn('fast');\n"
                          "}, function() {\n"
                          "jQuery(this).find('.box-button').fadeOut('fast');\n"
                          "});\n"
                          "jQuery('.small-graph-box .box-close').click(function() {\n"
                          "jQuery(this).closest('.small-graph-box').fadeOut(200);\n"
                          "return false;\n"
                          "});\n"

                          "//CHARTS\n"
                          "function gd(year, day, month) {\n"
                          "return new Date(year, month - 1, day).getTime();\n"
                          "}\n"

                          "graphArea2 = Morris.Area({\n"
                          "element: 'hero-area',\n"
                          "padding: 10,\n"
                          "behaveLikeLine: true,\n"
                          "gridEnabled: false,\n"
                          "gridLineColor: '#dddddd',\n"
                          "axes: true,\n"
                          "resize: true,\n"
                          "smooth:true,\n"
                          "pointSize: 0,\n"
                          "lineWidth: 0,\n"
                          "fillOpacity:0.85,\n"
                          "data: [\n"
                          "{period: '2015 Q1', iphone: 2668, ipad: null, itouch: 2649},\n"
                          "{period: '2015 Q2', iphone: 15780, ipad: 13799, itouch: 12051},\n"
                          "{period: '2015 Q3', iphone: 12920, ipad: 10975, itouch: 9910},\n"
                          "{period: '2015 Q4', iphone: 8770, ipad: 6600, itouch: 6695},\n"
                          "{period: '2016 Q1', iphone: 10820, ipad: 10924, itouch: 12300},\n"
                          "{period: '2016 Q2', iphone: 9680, ipad: 9010, itouch: 7891},\n"
                          "{period: '2016 Q3', iphone: 4830, ipad: 3805, itouch: 1598},\n"
                          "{period: '2016 Q4', iphone: 15083, ipad: 8977, itouch: 5185},\n"
                          "{period: '2017 Q1', iphone: 10697, ipad: 4470, itouch: 2038},\n"

                          "],\n"
                          "lineColors:['#eb6f6f','#926383','#eb6f6f'],\n"
                          "xkey: 'period',\n"
                          "redraw: true,\n"
                          "ykeys: ['iphone', 'ipad', 'itouch'],\n"
                          "labels: ['Todas as medições', 'Retorno de tensão', 'Unica medida'],\n"
                          "pointSize: 2,\n"
                          "hideHover: 'auto',\n"
                          "resize: true\n"
                          "});\n");


      P(corpoHTMLSys5) = ("});\n"
                          "</script>\n"
                          "<!-- calendar -->\n"
                          "<script type='text/javascript' src='https://cdn.rawgit.com/aragonxpd154/rid-pro/master/js/monthly.js'></script>\n"
                          "<script type='text/javascript' src='https://cdn.rawgit.com/aragonxpd154/rid-pro/master/js/marcossilva.js'></script>\n"


                          "</body>\n"
                          "</html>\n");




      server.printP(corpoHTMLSys);
      server.printP(corpoHTMLSys2);
      server.printP(corpoHTMLSys3);
      server.printP(corpoHTMLSys4);
      server.printP(corpoHTMLSys5);

      //server.printP(tensao);
      //server.printP(corpoHTMLSys3);
      //server.printP(corpoHTMLSys4);



      /* USAR O POST DE REQUISIÇÃO ABAIXO ARAGONES

         P(HTMLOPEN) = "<html>";
        P(background) = "<body style=background-color:BLACK>"; //set background to BLACK
        P(helloMsg) = "<center><font color=’green’> <h1>HOME - INTERNET -- CONTROL </h1></font></center>";
        P(FORMOPEN) = "<form action=formLogin.html method=POST name=LED id=LED><input type=hidden name=botao id=botao value=0";
        P(button1) = "<center><button name=tog1 value=1 type=submit style=font-weight:bold;color:GREEN;height:70px;width:145px>AC POWER RF FAN  On</button>";
        P(button2) = "<button name=tog2 value=2 type=submit style=font-weight:bold;color:red;height:70px;width:145px>AC POWER RF FAN Off</button>";
        P(FORMCLOSE) = "</form>";
        P(BODYCLOSE) = "</body>";
        P(HTMLCLOSE) = "</html>";

        server.printP(HTMLOPEN);
        server.printP(background);
        server.printP(helloMsg);
        server.printP(FORMOPEN);
        server.printP(button1);
        server.printP(button2);
        server.printP(FORMCLOSE);
        server.printP(BODYCLOSE);
        server.printP(HTMLCLOSE);
      */
    }
  }
  else
  {
    /* send a 401 error back causing the web browser to prompt the user for credentials */
    server.httpUnauthorized();
    if (type != WebServer::HEAD)
    {
      P(htmlError401) = ("<!--\n"
                         "Author: Marcos Silva\n"
                         "Author URL: http://aragones.esy.es\n"
                         "License: Creative Commons Attribution 3.0 Unported\n"
                         "License URL: http://creativecommons.org/licenses/by/3.0/\n"
                         "-->\n"
                         "<!DOCTYPE HTML>\n"
                         "<HTML><HEAD><TITLE>Error</TITLE>\n"
                         "<meta name='viewport' content='width=device-width, initial-scale=1'>\n"
                         "<meta http-equiv='Content-Type' content='text/html; charset=utf-8'/>\n"
                         "<meta name='keywords' content='Sistema de exemplo para erro de login e senha por Marcos Silva'/>\n"
                         "<script type='application/x-javascript'> addEventListener('load', function() { setTimeout(hideURLbar, 0); }, false); function hideURLbar(){ window.scrollTo(0,1); } </script>"
                         "<!-- bootstrap-css -->"
                         "<link rel='stylesheet' href='http://cdn.rawgit.com/aragonxpd154/libs/master/bootstrap.min.css'>"
                         "<!-- //bootstrap-css -->"
                         "<!-- Custom CSS -->"
                         "<link href='http://cdn.rawgit.com/aragonxpd154/libs/master/images/style.css' rel='stylesheet' type='text/css'/>"
                         "<link href='http://cdn.rawgit.com/aragonxpd154/libs/master/style-responsive.css' rel='stylesheet'/>"
                         "<!-- font CSS -->"
                         "<link href='http://fonts.googleapis.com/css?family=Roboto:400,100,100italic,300,300italic,400italic,500,500italic,700,700italic,900,900italic' rel='stylesheet' type='text/css'>"
                         "<!-- font-awesome icons -->"
                         "<link rel='stylesheet' href='https://cdn.rawgit.com/aragonxpd154/libs/master/font.css' type='text/css'/>"
                         "<link href='http://cdn.rawgit.com/aragonxpd154/libs/master/font-awesome.css' rel='stylesheet'>"
                         "<!-- //font-awesome icons -->"
                         "<script src='http://cdn.rawgit.com/aragonxpd154/libs/master/jquery2.0.3.min.js'></script>"
                         "</head>"
                         "<body>"
                         "<!--main content start-->"
                         "<div class='eror-w3'>"
                         "<div class='agile-info'>"
                         "<h3>SINTO MUITO</h3>"
                         "<h2>401</h2>"
                         "<p>Acesso não autorizado. Tente refazer o login novamente</p>"
                         "<a href='#'>Voltar ao Inicio</a>"
                         "</div>"
                         "</div>"
                         "<script src='http://cdn.rawgit.com/aragonxpd154/libs/master/bootstrap.js'></script>"
                         "<script src='http://cdn.rawgit.com/aragonxpd154/libs/master/jquery.dcjqaccordion.2.7.js'></script>"
                         "<script src='https://cdn.rawgit.com/aragonxpd154/libs/master/scripts.js'></script>"
                         "<script src='https://cdn.rawgit.com/aragonxpd154/libs/master/jquery.slimscroll.js'></script>"
                         "<script src='https://cdn.rawgit.com/aragonxpd154/libs/master/jquery.nicescroll.js'></script>"
                         "<!--[if lte IE 8]><script language='javascript' type='text/javascript' src='js/flot-chart/excanvas.min.js'></script><![endif]-->"
                         "<script src='https://cdn.rawgit.com/aragonxpd154/libs/master/jquery.scrollTo.js'></script>"
                         "</body>"
                         "</html>");

      server.printP(htmlError401);

    }
  }
}

void formCmd(WebServer &server, WebServer::ConnectionType type, char *url_tail, bool tail_complete)
{
  if (server.checkCredentials("dXNlcjp1c2Vy"))
  {
    if (type == WebServer::POST)
    {

      bool repeat;
      char name[16], value[16];
      do
      {


        repeat = server.readPOSTparam(name, 16, value, 16);


        /*Serial.print("name: ");
          Serial.println(name);
          Serial.print("value: ");
          Serial.println(value);
        */

        if (strncmp("tog1", name, 4) == 0)
        {
          break;
        }
        else if (strncmp("tog2", name, 4) == 0)
        {
          break;
        }
      } while (repeat);

      server.httpSeeOther(PREFIX "/private.html");

    }
  }
  else
  {
    server.httpUnauthorized();
  }
}


//LiquidCrystal_I2C lcd(0x27, 16, 2); // declara LCD, endereço e tipo
LiquidCrystal lcd (53, 51, 49, 47, 43, 33);

// Declarando as varíaveis globais e temporarias
int count = 0;

// Declarando as senhas paralelas
char senha [4] = {'8', '4', '4', '9'}; // TV Gazeta
char senha1 [4] = {'9', '4', '4', '8'}; // TV Vitoria

//const int sirenePin = 9; // Receber o sinal em 10 ou ambos paralelo
//const int sensorPin = 11; // Receber o sinal em 12 ou ambos paralelo
const int yellowPin = 11;
const int redPin = 12;
const int greenPin = 10;
const int audioPin = 9;
const int duration = 200;
const byte LINHAS = 4; // Quatro linhas
const byte COLUNAS = 3; // Três colunas
char keys[LINHAS][COLUNAS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};// definição do layout do teclado
byte linhasPins[LINHAS] = {7, 6, 5, 4}; // pinagem para as linhas do teclado
byte colunasPins[COLUNAS] = {8, 9, 12}; // pinagem para as colunas do teclado
// mapeamento do teclado
Keypad keypad = Keypad( makeKeymap(keys), linhasPins, colunasPins, LINHAS, COLUNAS );

void setup() {
  //lcd.init(); // inicializa o LCD caso seja ao modulo I2C
  lcd.begin(16, 2); // inicia o LCD caso seja ao modulo Serial
  //lcd.backlight(); // com backlight caso seja comunicação ao modulo I2C
  Serial.begin(9600); // inicializa serial
  // modo dos pinos de audio e LEDs
  pinMode(audioPin, OUTPUT);
  pinMode(yellowPin, OUTPUT);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  lcd.clear();// limpa LCD
  key_init();// inicializa processo
}

void loop() {
  
  char key = keypad.getKey(); // obtém informação do teclado
  if (key != NO_KEY) { // se foi teclado algo
    if (key == '#') {// se foi teclado #
      code_entry_init(); // mensagem, som e LED
      int entrada = 0; // variável de apoio; números de entradas feitas via teclado
      while (count < 4 ) { // enquanto não entrou os 4 números necessários para a senha
        char key = keypad.getKey(); // obtém informação do teclado
        
        if (key != NO_KEY) { // se foi teclado algo
          entrada += 1; // aumenta contrador de entradas
          tone(audioPin, 1080, 100); // sinal audível
          delay(duration);
          noTone(audioPin);
          if (key == senha[count])count += 1; // verifica na sequencia da senha, se correto aumenta contador da senha
          if (key == senha1 [count])count += 1; // verifica na sequencia da senha, se correto aumenta contador da senha1
          if ( count == 4 ) {
            untravado(); // chegou a 4 digitos corretos, libera acesso
          }
          if ((key == '#') || (entrada == 4)) { // foi teclado # ou 4 entradas incorretas
            key_init();// inicializa
            break;// interrompe loop
          }
        }
      }
    }
    if (key == '*') { // se foi teclado *
      old_senha_check();// mensagem para entrar a senha antiga
      int entrada = 0;
      while (count < 4 ) {
        char key = keypad.getKey();
        if (key != NO_KEY) {
          entrada += 1;
          tone(audioPin, 1080, 100);
          delay(duration);
          noTone(audioPin);
          if (key == senha[count])count += 1;
          if ( count == 4 ) { // foi teclado a senha antiga corretamente
            solicitar_nova_senha();// chama função para entrada da nova senha
          }
          if ((key == '*') || (entrada == 4)) { // foi teclado * ou entrou 4 números errados
            key_init();// inicializa
            break; // interrompe loop
          }
        }
      }
    }
  }
}

void travado() {
  lcd.clear();
  lcd.print("    ACESSO,");
  lcd.setCursor(0, 1);
  lcd.print("    NEGADO!");
  for (int i = 0; i < 11; i++) {
    tone(audioPin, 1080, 100);
    digitalWrite(yellowPin, LOW);
    digitalWrite(redPin, HIGH);
    delay(duration);
    noTone(audioPin);
    digitalWrite(redPin, LOW);
    delay(100);
  }
  delay(1000);
}



void solicitar_nova_senha() {
  new_senha_entry(); // mensagem, som e LED
  int entrada = 0; // inicializa entrada
  while (count < 4) { // enquanto contrador for menor que 4
    char key = keypad.getKey(); // obtem informação do teclado
    if (key != NO_KEY) { // se algo foi teclado
      entrada += 1; // aumenta contador de entrada
      tone(audioPin, 1080, 100); // tom para cada dígito
      delay(duration);
      noTone(audioPin);
      senha[count] = key; // armamazena o novo dígito
      count += 1; // próximo dígito
      if (count == 4) break; // chegou a 4 digitos, interrompe loop
      if ((key == '*') || (entrada == 4)) { // foi telcado * 4 entradas
        key_init();// inicializa sistema
        break; // mata o void
      }
    }
  }
}


void new_senha_entry() {
  // mensagem no display
  lcd.clear();
  lcd.print("   Nova Senha");
  count = 0;
  lcd.setCursor(0, 1);
  lcd.print("    Tecle *");
  // gera sinal audível
  tone(audioPin, 1500, 100);
  delay(duration);
  noTone(audioPin);
  tone(audioPin, 1500, 100);
  delay(duration);
  noTone(audioPin);
  tone(audioPin, 1500, 100);
  delay(duration);
  noTone(audioPin);
  // somente LED amarelo aceso
  digitalWrite(redPin, LOW);
  digitalWrite(yellowPin, HIGH);
  digitalWrite(greenPin, LOW);
}

void old_senha_check() {
  // mensagem no display
  lcd.clear();
  lcd.print("  Senha antiga?");
  count = 0;
  lcd.setCursor(0, 1);
  lcd.print("    Tecle *");
  // gera tom audível
  tone(audioPin, 1500, 100);
  delay(duration);
  noTone(audioPin);
  tone(audioPin, 1500, 100);
  delay(duration);
  noTone(audioPin);
  tone(audioPin, 1500, 100);
  delay(duration);
  noTone(audioPin);
  // somente LED amarelo aceso
  digitalWrite(redPin, LOW);
  digitalWrite(yellowPin, HIGH);
  digitalWrite(greenPin, LOW);
}


void key_init () {
  // mensagem no display
  lcd.clear();
  lcd.print("  Bem vindo...");
  lcd.setCursor(0, 1);
  lcd.print("  Tecle: # ou *");
  count = 0;// contador para zero
  // somente LED vermelho aceso
  digitalWrite(redPin, HIGH);
  digitalWrite(yellowPin, LOW);
  digitalWrite(greenPin, LOW);
  // gera tom audível
  tone(audioPin, 1080, 100);
  delay(duration);
  noTone(audioPin);
  tone(audioPin, 980, 100);
  delay(duration);
  noTone(audioPin);
  tone(audioPin, 770, 100);
  delay(duration);
  noTone(audioPin);
}

void code_entry_init() {
  // mensagem no display
  lcd.clear();
  lcd.print(" Entre a Senha:");
  count = 0; // contador para zero
  // gera sinal audível
  tone(audioPin, 1500, 100);
  delay(duration);
  noTone(audioPin);
  tone(audioPin, 1500, 100);
  delay(duration);
  noTone(audioPin);
  tone(audioPin, 1500, 100);
  delay(duration);
  noTone(audioPin);
  // somente LED amarelo aceso
  digitalWrite(redPin, LOW);
  digitalWrite(yellowPin, HIGH);
  digitalWrite(greenPin, LOW);
}

void untravado() {
  // mensagem no display
  lcd.clear();
  lcd.print("Acesso Liberado!");
  // somente LED verde aceso
  digitalWrite(redPin, LOW);
  digitalWrite(yellowPin, LOW);
  // pisca LED verde e gera sinal audível
  for (int x = 0; x < 5; x++) {
    digitalWrite(greenPin, HIGH);
    tone(audioPin, 2000, 100);
    delay(duration);
    noTone(audioPin);
    digitalWrite(greenPin, LOW);
    tone(audioPin, 2000, 100);
    delay(duration);
    noTone(audioPin);
    delay(250);
  }
}

void travado_sinal() {
  //mensagem no display

  lcd.clear();
  lcd.print("Digite '#' para sair");
  // Detona LED Verde
  digitalWrite(redPin, LOW);
  digitalWrite(yellowPin, LOW);
  // piscar o LED verde e gerar sinal audivel
  loop();
}

