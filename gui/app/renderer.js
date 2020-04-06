// This file is required by the index.html file and will
// be executed in the renderer process for that window.
// No Node.js APIs are available in this process because
// `nodeIntegration` is turned off. Use `preload.js` to
// selectively enable features needed in the rendering
// process.

let {PythonShell} = require("python-shell")

var position_s1 = 0;
var position_s2 = 0;
var speed_s1 = 0;
var speed_s2 = 0;

function testS1() {
  console.log('Stepper1-test!')
  position_s1 = document.getElementById("stepper1_pos").value
  console.log(position_s1)
  
  let pyshell = new PythonShell("serial-write.py");
  pyshell.send("<200>");
  pyshell.on("message", function (message) {
    console.log(message);
  });
  pyshell.end(function (err, code) {
    if (err) throw err;
    console.log("The exit code was: " + code);
  });
}

function stopS1() {
  console.log('Stepper1-stop!')
}

function testS2() {
  console.log('Stepper2-test!')
  position_s2 = document.getElementById("stepper1_pos").value
  console.log(position_s2)
}

function stopS2() {
  console.log('Stepper2-stop!')
}

window.onload = function() {
  document.querySelector('#btn-test-s1').addEventListener('click', () => {
    testS1()
  });
  document.querySelector('#btn-stop-s1').addEventListener('click', () => {
    stopS1()
  });
  document.querySelector('#btn-test-s2').addEventListener('click', () => {
    testS2()
  });
  document.querySelector('#btn-stop-s2').addEventListener('click', () => {
    stopS2()
  });
}
