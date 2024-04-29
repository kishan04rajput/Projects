var currentPlayer = "X";

function changeValue() {
    if (this.textContent === " ") {
        this.textContent = currentPlayer;
        checkWinner();
        togglePlayer();
    }
}

function togglePlayer() {
    currentPlayer = currentPlayer === "X" ? "O" : "X";
}

function checkWinner() {
    // Array of winning combinations
    const winConditions = [
        ["zz", "zo", "zt"], ["oz", "oo", "ot"], ["tz", "to", "tt"], // Rows
        ["zz", "oz", "tz"], ["zo", "oo", "to"], ["zt", "ot", "tt"], // Columns
        ["zz", "oo", "tt"], ["zt", "oo", "oz"] // Diagonals
    ];

    // Check each winning combination
    for (const condition of winConditions) {
        const [a, b, c] = condition;
        if (document.getElementById(a).textContent !== " " &&
            document.getElementById(a).textContent === document.getElementById(b).textContent &&
            document.getElementById(a).textContent === document.getElementById(c).textContent) {
            alert(currentPlayer + " wins!");
            resetBoard();
            return;
        }
    }
    // Check for draw
    if (isBoardFull()) {
        alert("It's a draw!");
        resetBoard();
    }
}

function isBoardFull() {
    for (var i = 0; i < squares.length; i++) {
        if (squares[i].textContent === " ") {
            return false;
        }
    }
    return true;
}

function resetBoard() {
    for (var i = 0; i < squares.length; i++) {
        squares[i].textContent = " ";
    }
}

var squares = document.querySelectorAll('td');
for (var i = 0; i < squares.length; i++) {
    squares[i].addEventListener("click", changeValue);
}
