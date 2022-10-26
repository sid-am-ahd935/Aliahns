const socket = io();
let name;
let messageArea = document.getElementById("message");
let chatBox = document.querySelector(".chat_box");

do {
  name = prompt("Please Enter your name : ");
} while (!name);

messageArea.addEventListener("keyup", (e) => {
  if (e.key == "Enter") {
    sendMessage(e.target.value);
  }
});

//function to send messages
let sendMessage = (message) => {
  let msg = {
    user: name,
    message: message.trim(),
  };

  //append message
  appendMessage(msg, "right");
  messageArea.value = "";
  scrollToBottom();

  //send the message to server
  socket.emit("message", msg);
};

let appendMessage = (msg, type) => {
  let span = document.createElement("span");
  span.classList.add(type);

  let chat = `
        <h3>${msg.user}</h3>
        <p>${msg.message}</p>
    `;

  span.innerHTML = chat;
  chatBox.appendChild(span);
};

// Recieve messages
socket.on("message", (msg) => {
  appendMessage(msg, "left");
  scrollToBottom();
});

//auto scrolling
function scrollToBottom() {
  chatBox.scrollTop = chatBox.scrollHeight;
}
