const char homepage[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<head>
    <style>
        td, th{
            border-bottom: 1px dotted #000;
        }
    </style>
</head>
<body>
    <a href="/login">
        <button type="button">Login</button>
    </a>
    <div id="container"></div>
    <script>
        var func_data_load = async () => {
            await fetch(window.location.origin + "/fileData", { method: "GET" })
                .then(res => res.json())
                .then((json) => {
                    console.log(json);
                    var table = document.createElement("table");
                    var col = [];
                    var tr = table.insertRow(-1);
                    for (var i = 0; i < json.length; i++) {
                        for (var key in json[i]) {
                            if (col.indexOf(key) === -1) {
                                col.push(key);
                            }
                        }
                    }
                    var th = document.createElement("th");
                    th.innerHTML = "File No.";
                    tr.appendChild(th);
                    var th = document.createElement("th");
                    th.innerHTML = "File Name";
                    tr.appendChild(th);
                    for (var i = 0; i < json.length; i++) {

                        tr = table.insertRow(-1);

                        for (var j = 0; j < col.length; j++) {
                            var tabCell = tr.insertCell(-1);
                            if (isNaN(json[i][col[j]]))
                                tabCell.innerHTML = `<a href="/download?file=` + json[i][col[j]] + `">` + json[i][col[[j]]] + `</a>`;
                            else
                                tabCell.innerHTML = json[i][col[j]];
                        }
                    }
                    var divContainer = document.getElementById("container");
                    divContainer.innerHTML = "";
                    divContainer.appendChild(table);

                }).catch((err) => {
                    var h1 = document.createElement("h1");
                    h1.innerHTML = "No Notification is there...";
                    var divContainer = document.getElementById("container");
                    divContainer.innerHTML = "";
                    divContainer.appendChild(h1);
                });
        };
        func_data_load();
    </script>
</body>

</html>
)=====";
