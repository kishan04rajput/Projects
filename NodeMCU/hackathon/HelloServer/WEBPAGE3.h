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
          <tr colspan="2">
            <td>Upload File:</td>
          </tr>
          <tr>
            <td>File:</td>
            <td><input type="file" name="fileUpload" /></td>
          </tr>
          <tr colspan="2">
            <td><input type="submit" value="Submit" title="UploadFile"/></td>
          </tr>
        </form>
      <tr colspan="2">
          <td><a href="/"><button title="Go To Home Page">HomePage</button></a> </td>
        </tr>
      <tr colspan="2">
          <td><a href="/deleteportal"><button title="DeleteNotification">Delete</button></a> </td>
        </tr>
      </table>
    </div>
  </body>
</html>
)=====";
