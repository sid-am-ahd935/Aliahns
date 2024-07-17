import React, { Component } from "react";
import { QRCodeSVG } from "qrcode.react";
import moment from "moment-timezone";
import Swal from "sweetalert2";
import styled, { keyframes } from "styled-components";

// Define scanning animation using styled-components
const scanningAnimation = keyframes`
  0% {
    transform: translateY(0);
  }
  50% {
    transform: translateY(-5500%); /* Move from top to bottom */
  }
  100% {
    transform: translateY(0);
  }
`;

// Styled component for scanning animation
const ScanningLine = styled.div`
  height: 2px;
  width: 100%;
  background-color: #4caf50; /* Green color for scanning line */
  position: absolute;
  top: 0;
  left: 0;
  animation: ${scanningAnimation} 3s linear infinite;
`;

class Qr extends Component {
  constructor() {
    super();
    this.state = {
      message: "",
      scanning: false
    };
  }

  speak = (text) => {
    const utterance = new SpeechSynthesisUtterance(text);
    utterance.rate = 1.2;
    window.speechSynthesis.speak(utterance);
  };

  checkTime = () => {
    const currentTime = moment.tz("Asia/Kolkata");
    const fixedTime = moment.tz("10:00", "HH:mm", "Asia/Kolkata");

    if (currentTime.isAfter(fixedTime)) {
      Swal.fire({
        icon: "error",
        title: "Oops...",
        text: "Sorry, You are late!"
      });
      this.speak("Oops.. Sorry, You are late!");
    } else {
      Swal.fire({
        icon: "success",
        title: "Welcome to work!",
        showConfirmButton: false,
        timer: 1500
      });
      this.speak("Welcome to work!");
    }
  };

  handleScan = () => {
    // Simulate scanning animation for 3 seconds
    this.setState({ scanning: true }, () => {
      setTimeout(() => {
        this.setState({ scanning: false });
        this.checkTime();
      }, 4500);
    });
  };

  render() {
    const { message, scanning } = this.state;

    return (
      <div style={{ position: "relative", width: "100%", height: "100%" }}>
        <QRCodeSVG value={message} size={110} />
        <div style={{ position: "relative", width: "100%", height: "100%" }}>
          {scanning && <ScanningLine />}
        </div>
        <p>{message}</p>
        <button onClick={this.handleScan}>Scan QR Code</button>
      </div>
    );
  }
}

export default Qr;
