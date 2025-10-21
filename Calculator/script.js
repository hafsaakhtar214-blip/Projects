document.getElementById("dark").onclick = function () {
    document.body.classList.toggle("dark");
}
const input = document.querySelector('#textarea');
const buttons = document.querySelectorAll('.btn');
let result = "";

buttons.forEach(btn => {
    btn.addEventListener('click', () => {
        const id = btn.id;

        if (id === "ac") {
            result = clear(result)
        }
        else if (id === "delete") {
            remove(result);
        }
        else if (id === "equal") {
            calculate(result);
        }
        else if (id === "percent") {
            result = (parseFloat(result) / 100).toString();
        }
        else if (id === "divide") {
            result += "/";
        }
        else if (id === "multiple") {
            result += "*";
        }
        else if (id === "subtract") {
            result += "-";
        }
        else if (id === "plus") {
            result += "+";
        } else {
            result += btn.innerHTML;
        }

        input.value = result || "0";
    });
});
function calculate(r)
 {
    try {
        result = eval(result).toString();
    }
    catch {
        result = "ERROR"
    }
}
function clear(r) {
    return r = "";
}

function remove(r) {
    result = result.slice(0, -1);
}

