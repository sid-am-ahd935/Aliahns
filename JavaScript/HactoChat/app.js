const express = require("express");
const app = express();
const http = require("http").createServer(app);

app.use(express.static(__dirname + "/public"));

app.get("/", (req, res) => {
  res.sendFile(__dirname + "/index.html");
});

http.listen(5000, () => {
  console.log("server is running at http://localhost:5000");
});

const io = require("socket.io")(http);

io.on("connection", (socket) => {
  console.log("User Connected !!");

  socket.on("message", (msg) => {
    socket.broadcast.emit("message", msg);
  });
});
