import React, { Component } from "react";
import { QRCodeSVG } from "qrcode.react";
import moment from "moment-timezone";
import Swal from "sweetalert2";

class Qr extends Component {
  constructor() {
    super();
    this.state = {
      message: ""
    };
  }

  checkTime = () => {
    const currentTime = moment.tz("Asia/Kolkata");
    const fixedTime = moment.tz("10:00", "HH:mm", "Asia/Kolkata");

    if (currentTime.isAfter(fixedTime)) {
      Swal.fire({
        icon: "error",
        title: "Oops...",
        text: "Sorry, You are late!"
      });
    } else {
      Swal.fire({
        position: "top-end",
        icon: "success",
        title: "Welcome to work!",
        // showConfirmButton: false,
        // timer: 1500
      });
    }
  };

  handleScan = () => {
    this.checkTime();
  };

  render() {
    const { message } = this.state;

    return (
      <div>
        <QRCodeSVG value={message} size={110} />
        <p>{message}</p>
        <button onClick={this.handleScan}>Scan QR Code</button>
      </div>
    );
  }
}

export default Qr;
