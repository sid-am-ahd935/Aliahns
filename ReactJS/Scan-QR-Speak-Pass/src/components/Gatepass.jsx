import React from "react";
import './css/Mycss.css';
import Qr from './Qr';
import Avatar from '@mui/material/Avatar';

const Gatepass = () => {
    return (
        <>
            <div className="container-fluid">
                <div className="card" style={{ width: '18rem', height: '26rem'}}>
                    <div className="card-body">
                        <Avatar alt="Rajasree" src="/img/me.jpg" sx={{ width: 120, height: 120 }} />
                    <div className="first">
                        <h4 className="card-title1">Rajasree Laha</h4>
                    </div> 
                    <div className="second">   
                        <h6 className="card-title"><i>Aspiring MERN Stack Developer</i></h6>
                    </div> 
                    <div className="third"> 
                        <p className="card-text"><b>Id :</b> 56557</p>
                    </div>
                    <div className="qr">
                         <Qr />
                    </div>
                    </div>
                </div>
            </div>
        </>
    );
}

export default Gatepass;
