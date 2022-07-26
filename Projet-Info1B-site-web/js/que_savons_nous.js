function ID(id){
	return document.getElementById(id);
}

function inser(num){
	document.formcalcul.result.value = document.formcalcul.result.value + num;
}

function result(){
	var eq = document.formcalcul.result.value;
	if (eq){
		document.formcalcul.result.value = eval(eq);
	}
}

function cancel(){
	document.formcalcul.result.value = "";
}

function back(){
	var eq = document.formcalcul.result.value;
	if(eq){
		document.formcalcul.result.value = eq.substring(0, eq.length - 1);
	}
}

function function_cos(){
	var eq = document.formcalcul.result.value;
	document.formcalcul.result.value = Math.cos(eq);
}


function function_sin(){
	var eq = document.formcalcul.result.value;
	document.formcalcul.result.value = Math.sin(eq);
}


function function_tan(){
	var eq = document.formcalcul.result.value;
	document.formcalcul.result.value = Math.tan(eq);
}

function facto(){
	var eq = document.formcalcul.result.value;
	var res = 1;
	if (eq==0) {
		res = 1;
	}
	else{
		for(var i=2; i<=eq; i++){
			res = res * i;
		}
	}
	document.formcalcul.result.value = res;
}

function carre(){
	var eq = document.formcalcul.result.value;
	document.formcalcul.result.value = eval(eq)*eval(eq);
}

function sqrt(){
	var eq = document.formcalcul.result.value;
	document.formcalcul.result.value = Math.sqrt(eq);
}

function log(){
	var eq = document.formcalcul.result.value;
	document.formcalcul.result.value = Math.log10(eq);
}

function ln(){
	var eq = document.formcalcul.result.value;
	document.formcalcul.result.value = Math.log(eq);
}

function exp(){
	var eq = document.formcalcul.result.value;
	document.formcalcul.result.value = Math.exp(eq);
}

function draw(){
	var Cvas = document.getElementById("dessin");
	var ctx = Cvas.getContext("2d");

	ctx.beginPath();
	ctx.moveTo(89.23, 59.28);
	ctx.bezierCurveTo(91.91, 52.82, 94.90, 46.85, 104.45, 45.36);
	ctx.stroke();
	ctx.moveTo(104.45, 45.36);
	ctx.bezierCurveTo(115.49, 42.67, 120.56, 45.06, 126.53, 46.26);
	ctx.stroke();
	ctx.moveTo(126.53, 46.26);
	ctx.bezierCurveTo(126.53, 46.26, 152.19, 54.61, 152.19, 54.61);
	ctx.stroke();
	ctx.moveTo(152.19, 54.61);
	ctx.bezierCurveTo(152.19, 54.61, 142.65, 55.80, 142.65, 55.80);
	ctx.stroke();
	ctx.moveTo(142.65, 55.80);
	ctx.bezierCurveTo(142.65, 55.80, 121.16, 49.24, 121.16, 49.24);
	ctx.stroke();
	ctx.moveTo(121.16, 49.24);
	ctx.bezierCurveTo(114.89, 45.05, 109.22, 46.85, 102.06, 51.03);
	ctx.stroke();
	ctx.moveTo(102.06, 51.03);
	ctx.bezierCurveTo(96.69, 54.01, 94.00, 57.30, 92.21, 59.98);
	ctx.stroke();
	ctx.moveTo(92.21, 59.98);
	ctx.bezierCurveTo(98.18, 62.97, 104.75, 63.86, 111.01, 62.67);
	ctx.stroke();
	ctx.moveTo(111.01, 62.67);
	ctx.bezierCurveTo(119.07, 64.16, 125.93, 59.09, 133.69, 56.70);
	ctx.stroke();
	ctx.moveTo(133.69, 56.70);
	ctx.bezierCurveTo(141.15, 53.42, 148.32, 49.54, 152.79, 42.38);
	ctx.stroke();
	ctx.moveTo(152.79, 42.38);
	ctx.bezierCurveTo(144.73, 33.12, 131.01, 29.54, 118.47, 27.45);
	ctx.stroke();
	ctx.moveTo(118.47, 27.45);
	ctx.bezierCurveTo(106.83, 25.66, 98.48, 28.35, 89.53, 36.41);
	ctx.stroke();
	ctx.moveTo(89.53, 36.41);
	ctx.bezierCurveTo(76.10, 54.61, 72.22, 77.28, 65.65, 96.99);
	ctx.stroke();
	ctx.moveTo(65.65, 96.99);
	ctx.bezierCurveTo(64.16, 98.48, 63.27, 100.27, 65.65, 102.06);
	ctx.stroke();
	ctx.moveTo(65.65, 102.06);
	ctx.bezierCurveTo(70.73, 107.13, 83.86, 103.85, 80.87, 105.64);
	ctx.stroke();
	ctx.moveTo(80.87, 105.64);
	ctx.bezierCurveTo(83.56, 105.64, 83.56, 103.55, 82.36, 101.76);
	ctx.stroke();
	ctx.moveTo(82.36, 101.76);
	ctx.bezierCurveTo(77.59, 100.87, 73.41, 102.36, 69.53, 108.33);
	ctx.stroke();
	ctx.moveTo(69.53, 108.33);
	ctx.bezierCurveTo(68.64, 112.50, 67.44, 116.38, 67.14, 121.46);
	ctx.stroke();
	ctx.moveTo(67.14, 121.46);
	ctx.bezierCurveTo(67.74, 124.14, 69.53, 127.43, 68.04, 129.51);
	ctx.stroke();
	ctx.moveTo(68.04, 129.51);
	ctx.bezierCurveTo(63.27, 132.50, 60.58, 131.31, 58.49, 129.51);
	ctx.stroke();
	ctx.moveTo(58.49, 129.51);
	ctx.bezierCurveTo(56.40, 123.25, 58.79, 122.95, 60.58, 120.56);
	ctx.stroke();
	ctx.moveTo(60.58, 120.56);
	ctx.bezierCurveTo(60.58, 120.56, 67.74, 123.25, 67.74, 123.25);
	ctx.stroke();
	ctx.moveTo(67.74, 123.25);
	ctx.bezierCurveTo(67.74, 123.25, 72.52, 118.47, 72.52, 118.47);
	ctx.stroke();
	ctx.moveTo(72.52, 118.47);
	ctx.bezierCurveTo(81.47, 119.97, 80.56, 121.46, 82.66, 121.46);
	ctx.stroke();
	ctx.moveTo(82.66, 121.46);
	ctx.bezierCurveTo(82.66, 121.46, 100.27, 125.93, 100.27, 124.93);
	ctx.stroke();
	ctx.moveTo(100.27, 124.93);
	ctx.bezierCurveTo(100.27, 124.93, 89.23, 133.39, 89.23, 133.39);
	ctx.stroke();
	ctx.moveTo(89.23, 133.39);
	ctx.bezierCurveTo(83.86, 136.98, 78.78, 142.45, 72.81, 140.85);
	ctx.stroke();
	ctx.moveTo(72.81, 140.85);
	ctx.bezierCurveTo(67.44, 140.46, 62.07, 140.85, 61.47, 136.68);
	ctx.stroke();
	ctx.moveTo(61.47, 136.68);
	ctx.bezierCurveTo(59.98, 134.29, 62.97, 132.20, 65.65, 131.01);
	ctx.stroke();
	ctx.moveTo(65.65, 131.01);
	ctx.bezierCurveTo(70.73, 128.92, 76.69, 129.51, 82.66, 129.81);
	ctx.stroke();
	ctx.closePath();
}

