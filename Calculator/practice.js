const input = document.querySelector('input[type="text"]');
const buttons = document.querySelectorAll('.btn button');
let result = "";
buttons.forEach(btn => {
    btn.addEventListener('click', () => {
        const id = btn.id;
        if(id==="ac")
        {
            clear(result);
        }
        if(id==="delete")
        {
            remove(result);
        }
        if(id==="equal")
        {
            calculate(result);
        }
        else{
            result+= btn.innerText;
        }
    
        clear(result);
    });
});

function clear(r) {
    document.getElementById("display").clear;
    r = "";
}

function remove(r) {
    result = result.slice(0, -1);
}

function calculate(r) {
    try {
        result = eval(result).toString();
    }
   catch{
    result="ERROR"
   }
}