function changeValue(){
    if(this.textContent === " "){
        this.textContent = "X";
    }
    else if(this.textContent === "X"){
        this.textContent = "O";
    }
    else{
        this.textContent = " ";
    }
}

var squares = document.querySelectorAll('td');
for(var i=0;i<squares.length;i++){
    squares[i].addEventListener("click",changeValue);
}