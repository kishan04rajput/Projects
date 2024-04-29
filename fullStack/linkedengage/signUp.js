function resetErrors() {
  errors = document.getElementsByClassName("formError");
  for (let item of errors) {
    item.innerHTML = "";
  }
}

function setError(id, error) {
  document.getElementById(id).innerHTML = error;
}

function validateForm() {
  resetErrors();



  var password = document.getElementById("pass").value;
  var rpassword = document.getElementById("rpass").value;
  if (rpassword != password) {
    setError("passError", "*");
    setError("rpassError", "*");
    return false;
  }

  return true;
}
