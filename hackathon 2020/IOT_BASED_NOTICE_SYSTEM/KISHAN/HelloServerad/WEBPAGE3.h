//const char backend_page[] PROGMEM="";

//Authrenetication ke baad ka page.
const char err[] PROGMEM = R"=====(
<script>
  alert("Wrong Username or password");
  window.location.replace(window.location.origin+"/login");
</script>
)=====";

//Authrenetication ke baad ka page.
const char success[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
  <head>
    <Title>UPLOAD FILE</Title>
  </head>
  <body>
    <div>
      <table>
        <form action="/datahandling" method="POST" enctype="multipart/form-data" >
          <tr>
            <td><input type="file" name="fileUpload" /></td>
          </tr>
          <tr colspan="2">
            <td><input type="submit" value="Upload File" /></td>
          </tr>
        </form>
      <tr colspan="2">
          <td><a href="/"><button>Home Page</button></a> </td>
        </tr>
      </table>
    </div>
    <div>
      <form action="/Deleted" onsubmit="alert_box()">
       <br> <input type="submit" value="Delete File" /> 
      </form>
      <script>
        function alert_box(){
          alert("The file is deleted.");
        }
      </script>
    </div>
  </body>
</html>
)=====";
