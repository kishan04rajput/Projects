// Homepage || Firstpage




/*

  String msg(String FileName) {
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr += "<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr += "<title>HomePage</title>\n";

  ptr += "</head>\n";
  ptr += "<body>\n";
  ptr += "<div id=\"webpage\">\n";

  ptr += "<p>FileName: ";
  ptr += (String)FileName;

  ptr += "</body>\n";
  ptr += "</html>\n";
  //  return ptr;
  }
*/





char msg[] PROGMEM = R"=====(
  <html>
  <body>
    <a href="/login">
    <button type="button">Login</button>
    </a>
    <p>(String)FileName<br>
    </p>
    <div>
        <a href="/helloworld.txt">Helloworld.txt</a>
        <br>
    </div>
  </body>
  </html>
  )=====";
