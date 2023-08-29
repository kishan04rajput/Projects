//const char backend_page[] PROGMEM="";

const char err[] PROGMEM = R"=====(
<script>
  alert("Wrong Username or password");
  window.location.replace(window.location.origin+"/login");
</script>
)=====";

const char success[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
  <head>
    <Title>Login Page</Title>
  </head>
  <body>
    <div>
      <table>
        <form action="/datahandling" method="POST" enctype="multipart/form-data" >
          <tr colspan="2">
            <td>Upload File:</td>
          </tr>
          <tr>
            <td>File:</td>
            <td><input type="file" name="fileUpload" /></td>
          </tr>
          <tr colspan="2">
            <td><input type="submit" value="Submit" /></td>
          </tr>
        </form>
      <tr colspan="2">
          <td><a href="/"><button>HomePage</button></a> </td>
        </tr>
      </table>
    </div>
  </body>
</html>
)=====";
