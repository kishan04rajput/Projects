const char login_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
  <head>
    <Title>Login Page</Title>
  </head>
  <body>
    <div>
      <form action="/backend" method="POST">
        <table>
          <tr colspan="2">
            <td>Login to System</td>
          </tr>
          <tr>
            <td>Username:</td>
            <td><input type="text" name="txtUserName" /></td>
          </tr>
          <tr>
            <td>Password:</td>
            <td><input type="password" name="pwWatchword" /></td>
          </tr>
          <tr colspan="2">
            <td><input type="submit" value="Login" /></td>
          </tr>
        </table>
      </form>
    </div>
  </body>
</html>
)=====";
