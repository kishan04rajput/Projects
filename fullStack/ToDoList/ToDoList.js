document.addEventListener("DOMContentLoaded", function () {
    var addButton = document.getElementById("addRow");
    var tableBody = document.querySelector("tbody");

    addButton.addEventListener("click", function () {
        var newRow = document.createElement("tr");
        var checkBoxCell = document.createElement("td");
        var inputTextCell = document.createElement("td");

        var checkBox = document.createElement("input");
        checkBox.type = "checkbox";

        var inputText = document.createElement("input");
        inputText.type = "text";

        inputText.style.overflowWrap  = "break-word";
        inputText.style.maxWidth = "100%";

        checkBoxCell.appendChild(checkBox);
        inputTextCell.appendChild(inputText);

        newRow.appendChild(checkBoxCell);
        newRow.appendChild(inputTextCell);

        tableBody.appendChild(newRow);
    });

    var deleteRow = document.getElementById("deleteRow");
    deleteRow.addEventListener("click", function () {
        var rows = tableBody.getElementsByTagName("tr");

        for (var i = rows.length - 1; i >= 0; i--) {
            var row = rows[i];

            var checkBox = row.querySelector("input[type=checkbox]");

            if (checkBox.checked) {
                tableBody.removeChild(row);
            }
        }
    });
});
