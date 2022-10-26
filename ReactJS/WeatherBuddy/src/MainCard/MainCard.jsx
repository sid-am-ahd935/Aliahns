import React from 'react'
import { Card, Form} from 'react-bootstrap'
import {BsFillSunriseFill, BsFillSunsetFill, BsWind, BsSpeedometer2} from "react-icons/bs"
import { WiHumidity } from "react-icons/wi"
import {FiMinimize2, FiMaximize2} from "react-icons/fi"
import {FaLevelUpAlt} from "react-icons/fa"
import OverlayTrigger from 'react-bootstrap/OverlayTrigger';
import Tooltip from 'react-bootstrap/Tooltip';
import { useState } from 'react'
import { useEffect } from 'react'


const MainCard = () => {
	const [data, setData] = useState();
	const [city, setCity] = useState("kolkata");

	const url = `https://api.openweathermap.org/data/2.5/weather?q=${city}&appid=cd4be6e5522f7d1b8f2a7fb76a8cfbf8`;
	const getWeatherData = async()=>{
		const data = await fetch(url);
		const res = await data.json();
		console.log(res);
		setData(res);
	}
	// const isDay = data?.data[0].icon?.includes['d'];
	// const getTime = (timeStamp) => {
    //     return `${new Date(timeStamp * 1000).getHours()} : ${new Date(timeStamp * 1000).getMinutes()}`
    // }

	const getTime = (time) =>{
		const date = new Date(time*1000);
		const hours = date.getHours();
		const min = date.getMinutes();

		return (min > 10) ? (hours + ':' + min) : (hours + ":0" + min);
	}
	
	useEffect(()=>{
		getWeatherData();
	}, [city]);

	return (
		<div className='all shadow-g'>

			<Card className='search-card none'>
                <div className="heading">
                    <img src="./img/logo.jpg" alt="Weather Icon" />
                    <h3 style={{margin:"1rem"}}>Search any city here..</h3>
                </div>
                <Form >
                    <input type="text" name="cityName" value={city} required defaultValue={"kolkata"}
						onChange = {(e) =>{setCity(e.target.value)}}
					/>
                </Form>
            </Card>

			<hr /> <hr />

			{
				(!data?.name) ? <h3>No cities to fetch</h3> :
			<Card className="view-card none">
				<div className="heading d-flex justify-content-around align-items-center">
					<h3>{data && `${data.name} | ${data?.sys?.country}`}</h3>
					<h3>{data && Math.floor(data?.main?.temp - 273)} ℃</h3>
					<img src={data && `http://openweathermap.org/img/wn/${data?.weather[0]?.icon}@2x.png`} alt="weather condition image" />
				</div>
				<div className="first d-flex">
					<div className="left d-flex align-items-center">
						<OverlayTrigger
							placement={"top"}
							overlay={
								<Tooltip >
								maximum temp.
								</Tooltip>
							}
						>
							<button className="tooltip_btn">
							<FiMaximize2 className='icon' />
							</button>
						</OverlayTrigger>
						<h4>{data && Math.floor(data?.main?.temp_max - 273)} ℃</h4>
					</div>
					<div className="right d-flex align-items-center">
						<OverlayTrigger
							placement={"top"}
							overlay={
								<Tooltip>
								minimum temp.
								</Tooltip>
							}
						>
							<button className="tooltip_btn">
							<FiMinimize2 className='icon' />
							</button>
						</OverlayTrigger>
						<h4>{data && Math.floor(data?.main?.temp_min - 273)} ℃</h4>
					</div>
				</div>
				<div className="second d-flex">
					<div className="left d-flex align-items-center">
						<OverlayTrigger
							placement={"top"}
							overlay={
								<Tooltip >
								Humidity
								</Tooltip>
							}
						>
							<button className="tooltip_btn">
							<WiHumidity className='icon' />
							</button>
						</OverlayTrigger>
						<h4>{data && Math.floor(data?.main?.humidity)} %</h4>
					</div>
					<div className="right d-flex align-items-center">
						<OverlayTrigger
							placement={"top"}
							overlay={
								<Tooltip>
								Wind speed
								</Tooltip>
							}
						>
							<button className="tooltip_btn">
							<BsWind className='icon' />
							</button>
						</OverlayTrigger>
						<h4> {data && data?.wind?.speed} km/h</h4>
					</div>
				</div>
				<div className="third d-flex">
					<div className="left d-flex align-items-center">
						<OverlayTrigger
							placement={"top"}
							overlay={
								<Tooltip >
								Sunrise
								</Tooltip>
							}
						>
							<button className="tooltip_btn">
							<BsFillSunriseFill className='icon' />
							</button>
						</OverlayTrigger>
						{/* <h4> {data && (getTime(data?.sys[isDay ? "sunset" : "sunrise"]))}</h4> */}
						<h4>{data && getTime(data?.sys?.sunrise)} </h4>
					</div>
					<div className="right d-flex align-items-center">
						<OverlayTrigger
							placement={"top"}
							overlay={
								<Tooltip>
								Sunset
								</Tooltip>
							}
						>
							<button className="tooltip_btn">
							<BsFillSunsetFill className='icon' />
							</button>
						</OverlayTrigger>
						<h4>{data && getTime(data?.sys?.sunset)} </h4>
					</div>
				</div>
				<div className="fourth d-flex">
					<div className="left d-flex align-items-center">
						<OverlayTrigger
							placement={"top"}
							overlay={
								<Tooltip >
								Air Pressure
								</Tooltip>
							}
						>
							<button className="tooltip_btn">
							<BsSpeedometer2 className='icon' />
							</button>
						</OverlayTrigger>
						<h4>{data && data?.main?.pressure}</h4>
					</div>
					<div className="right d-flex align-items-center">
						<OverlayTrigger
							placement={"top"}
							overlay={
								<Tooltip>
								Height 
								</Tooltip>
							}
						>
							<button className="tooltip_btn">
							<FaLevelUpAlt className='icon' />
							</button>
						</OverlayTrigger>
						<h4>{data && Math.round(data?.coord?.lat)} Feet</h4>
					</div>
				</div>
			</Card>
			}
		</div>
	)
}

export default MainCard