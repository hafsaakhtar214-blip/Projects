const createRipple = (e) => {
    const button = e.currentTarget;

    const ripple = document.createElement("span");
    ripple.classList.add("ripple");

    const rect = button.getBoundingClientRect();
    const size = Math.max(rect.width, rect.height);
    ripple.style.width = ripple.style.height = size + "px";

    const x = e.clientX - rect.left - size / 2;
    const y = e.clientY - rect.top - size / 2;
    ripple.style.left = `${x}px`;
    ripple.style.top = `${y}px`;

    button.appendChild(ripple);

    ripple.addEventListener("animationend", () => {
        ripple.remove();
    });
};

let taskArray = [];
const today = new Date();
const formattedDate = today.toDateString();
document.getElementById("date").innerHTML = formattedDate;

document.getElementById("task").onclick = function (e) {
    createRipple(e);
    document.getElementById("ma").style.display = "block";
    document.getElementById("showcal").style.display = "none";
    renderTasks(taskArray);

}

document.getElementById("add-task").onclick = function (e) {
    createRipple(e);
    const container = document.querySelector(".container");
    if (container.style.display === "none" || container.style.display === "") {
        container.style.display = "block";
    }
    else {
        container.style.display = "none";
    }
};


document.getElementById("task-save").addEventListener("click", function (e) {
    createRipple(e);

    const name = document.getElementById("task-name").value.trim();
    const priority = document.getElementById("task-priority").value;
    const date = document.getElementById("task-date").value;

    if (!name || !priority || !date) {
        alert("Please fill in all fields.");
        return;
    }

    const task = { name, priority, date };
    taskArray.push(task);
    renderTasks(taskArray);
    document.getElementById("task-name").value = "";
    document.getElementById("task-priority").value = "";
    document.getElementById("task-date").value = "";
    document.querySelector(".container").style.display = "none";
});


function getPriorityColor(priority) {
    switch (priority.toLowerCase()) {
        case "low":
            return "green";
        case "normal":
            return "orange";
        case "high":
            return "red";
        default:
            return "black";
    }
}

function renderTasks(tasksToRender) {
    const oldTasks = document.querySelectorAll(".task-item");
    oldTasks.forEach(item => item.remove());

    tasksToRender.forEach(task => {
        const taskItem = document.createElement("div");
        taskItem.className = "task-item";
        taskItem.style.marginTop = "10px";
        taskItem.style.padding = "8px";
        taskItem.style.borderRadius = "8px";
        taskItem.style.backgroundColor = getPriorityColor(task.priority);
        taskItem.style.display = "flex";
        taskItem.style.alignItems = "center";
        taskItem.style.justifyContent = "space-between";

        const taskContent = document.createElement("div");
        taskContent.innerHTML = `
            <strong>${task.name}</strong><br>
            Priority: ${task.priority}<br>
            Due: ${task.date}
        `;

        const checkbox = document.createElement("input");
        checkbox.type = "checkbox";
        checkbox.style.transform = "scale(1.5)";
        checkbox.style.marginLeft = "10px";

        checkbox.addEventListener("change", function () {
            if (checkbox.checked) {
                taskArray = taskArray.filter(t => t !== task);
                renderTasks(taskArray);
                alert("Task completed!");
            }
        });

        taskItem.appendChild(taskContent);
        taskItem.appendChild(checkbox);
        document.getElementById("ma").appendChild(taskItem);
    });
}

document.getElementById("search").addEventListener("input", function () {
    const query = this.value.toLowerCase();
    const filtered = taskArray.filter(task =>
        task.name.toLowerCase().includes(query)
    );
    renderTasks(filtered);
});

{
    const monthYear = document.getElementById('month-year');
    const daysContainer = document.getElementById('days');
    const prevButton = document.getElementById('prev');
    const nextButton = document.getElementById('next');

    const months = ['January', 'February', 'March', 'April', 'May', 'June',
        'July', 'August', 'September', 'October', 'November', 'December'];

    let currentDate = new Date();
    const today = new Date();

    function renderCalendar(date) {
        const year = date.getFullYear();
        const month = date.getMonth();
        const firstDay = new Date(year, month, 1).getDay();
        const lastDay = new Date(year, month + 1, 0).getDate();
        monthYear.textContent = `${months[month]}, ${year}`;
        daysContainer.innerHTML = '';

        const prevMonthLastDay = new Date(year, month, 0).getDate();
        for (let i = firstDay; i > 0; i--) {
            const dayDiv = document.createElement("div");
            dayDiv.textContent = prevMonthLastDay - i + 1;
            daysContainer.appendChild(dayDiv);
        }
        for (let i = 1; i <= lastDay; i++) {
            const dayDiv = document.createElement('div');
            dayDiv.textContent = i;
            const thisDate = new Date(year, month, i);
            const dateString = thisDate.getFullYear() + '-' +
                String(thisDate.getMonth() + 1).padStart(2, '0') + '-' +
                String(thisDate.getDate()).padStart(2, '0');

            if (
                i === today.getDate() &&
                month === today.getMonth() &&
                year === today.getFullYear()
            ) {
                dayDiv.classList.add('today');
            }
            dayDiv.addEventListener("click", function () {
                const matchingTasks = taskArray.filter(t => t.date === dateString);
                document.getElementById("ma").style.display = "block";
                renderTasks(matchingTasks);
            });

            daysContainer.appendChild(dayDiv);
        }

        const lastDayWeekday = new Date(year, month, lastDay).getDay();
        const nextMonthStartDay = 6 - lastDayWeekday;
        for (let i = 1; i <= nextMonthStartDay; i++) {
            const dayDiv = document.createElement('div');
            dayDiv.textContent = i;
            daysContainer.appendChild(dayDiv);
        }
    }

    prevButton.addEventListener('click', function () {
        currentDate.setMonth(currentDate.getMonth() - 1);
        renderCalendar(currentDate);
    });

    nextButton.addEventListener('click', function () {
        currentDate.setMonth(currentDate.getMonth() + 1);
        renderCalendar(currentDate);
    });
    renderCalendar(currentDate);
}


document.getElementById("cal").onclick = function (e) {
    createRipple(e);
    document.getElementById("showcal").style.display = "block";
    document.getElementById("ma").style.display = "none";
};


document.getElementById("logoutbtn").onclick = function (e) {
    createRipple(e);
    alert("You have been successfully logged out!");
    document.getElementById("name").innerHTML = "";
};

const params = new URLSearchParams(window.location.search);
const namee = params.get("name");
if (namee) {
    document.getElementById("name").innerText = "Hi, " + namee;
}




