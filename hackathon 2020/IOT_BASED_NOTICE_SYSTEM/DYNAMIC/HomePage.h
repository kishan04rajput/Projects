const char msg[] PROGMEM = R"=====(
<html>

<body>
    <a href="/login">
        <button type="button">Login</button>
    </a>
    <div id="container"></div>
    <script>
        let res = await fetch(window.location.origin + "/fileData");
        if (res.ok) {
            var dataJSON = await res.json();
            var table = document.createElement("table");
            var col = [];
            for (var i = 0; i < dataJSON.length; i++) {
                for (var key in dataJSON[i]) {
                    if (col.indexOf(key) === -1) {
                        col.push(key);
                    }
                }
            }
            for (var i = 0; i < col.length; i++) {
                var th = document.createElement("th");
                th.innerHTML = col[i];
                tr.appendChild(th);
            }
            for (var i = 0; i < dataJSON.length; i++) {

                tr = table.insertRow(-1);

                for (var j = 0; j < col.length; j++) {
                    var tabCell = tr.insertCell(-1);
                    tabCell.innerHTML = dataJSON[i][col[j]];
                }
            }
            var divContainer = document.getElementById("container");
            divContainer.innerHTML = "";
            divContainer.appendChild(table);
        }
        else {
            alert("HTTP-Error: " + res.status);
        }
    </script>
</body>

</html>
)=====";
