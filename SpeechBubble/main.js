// import * as THREE from '../node_modules/three/build/three.module.js'

// const scene = new THREE.Scene();

// const camera  = new THREE.PerspectiveCamera(75,window.innerWidth/window.innerHeight,0.1, 100);

// const renderer = new THREE.WebGLRenderer({
//   canvas: document.querySelector('#bg'),
// });

// renderer.setPixelRatio (window.devicePixelRatio);
// renderer.setSize( window.innerWidth, window.innerHeight);

// //renderer.render(scene, camera)
// camera.position.setZ(30);
// camera.position.setX(0);
// camera.position.setY(0);

function sleep(ms) {
	return new Promise(resolve => setTimeout(resolve, ms));
  }

function DeleteAllElements()
{
	const myNode = document.getElementById("MainDiv");
	
	const MyChildren = myNode.children;
	for (var i = 0; i < MyChildren.length; i++)
	{
		if(MyChildren[i].id != "canvas")
		{
			MyChildren[i].remove();
		}
	}
	sleep(200).then(() => { myNode.removeEventListener("click", DeleteAllElements); });
}

var TestString = "What the fuck did you just say to about me, you little bitch? I'll have you know I garduated top of my class in the navy Seals, and I've been involved in numerous secret raids on Al-Queada, And I have over 300 confirmed kills. I am trained in Orangatang warefare and im the top of sniper in the entire US armed forces. you are nothing to me but another target. I will wipe you the fuck out with the precision the likes of which has never been seen before on this earth, Mark my fucking words"
function Speak(iter, P, Speed, Text)
{
	var C = "";
	for(var i = 0; i < iter; i++ ){
		//console.log(i);
		C += Text[i];
	}
	P.innerHTML = C;
	iter++;
	if(iter <= Text.length)
	{
		sleep(Speed).then(() => { Speak(iter, P, Speed, Text) });
	}
	else{
		const myNode = document.getElementById("MainDiv");
		const MyChildren = myNode.children;
		myNode.addEventListener("click", DeleteAllElements);
	}

	
}

function FadeInBubble(ID, Opacity)
{
	document.getElementById(ID).style.opacity = Opacity;

	

	if(Opacity >= 1)
	{
		
	}
	else
	{
		Opacity += 0.1;
		sleep(100).then(() => { FadeInBubble(ID, Opacity)});
	}


}
var canvas = document.getElementById("canvas")
var ctx = canvas.getContext("2d");
var background = new Image();
background.src = "NavySeal.jpg"
ctx.fillStyle = 'green';
ctx.fillRect(0, 10, 230, 100);

function CreateBubble(Talker, Text)
{
	const MainDiv = document.getElementById("MainDiv");
	const Bubble = document.createElement("div");
	const InnerText = document.createElement("p");
	const Speaker = document.createElement("div");
	Speaker.id = "SpeakerTitleBox"
	Bubble.id = "Speech";
	Bubble.innerHTML = "";
	MainDiv.appendChild(Bubble);
	Bubble.appendChild(InnerText);
	Bubble.appendChild(Speaker);
	Speaker.innerHTML = Talker;


	//FadeInBubble(Bubble.id, 0)

	Speak(0, InnerText, 10, Text);


	
}



var TestEr;
//CreateBubble("Jack Thorpe", TestString);


// Speaker, Message
CreateBubble("Navy Seal", TestString);








// const pointLight = new THREE.PointLight(0xffffff);
// pointLight.position.set(5,5,5);
// scene.add(pointLight);

// const ambientLight = new THREE.AmbientLight(0xffffff);
// scene.add(ambientLight);

// const geometry2 = new THREE.PlaneGeometry(50, 50);
// const material2 = new THREE.MeshStandardMaterial( { color: 0x00FF00});
// const ground = new THREE.Mesh(geometry2, material2);

// ground.rotation.x -= 0.7
// scene.add(ground);
// const SquareSize = 50;

// const raycaster = new THREE.Raycaster();
// const pointer = new THREE.Vector2();

// const UI = document.getElementsByClassName("UI1");

// function onPointerMove( event ) {

// 	// calculate pointer position in normalized device coordinates
// 	// (-1 to +1) for both components

// 	pointer.x = ( event.clientX / window.innerWidth ) * 2 - 1;
// 	pointer.y = - ( event.clientY / window.innerHeight ) * 2 + 1;

// 	// for(var i = 1; i < UI.length; i++){
// 	// 	var a = UI[i];
// 	// 	a.hidden = !a.hidden;
// 	//  }



// }

// window.addEventListener( 'pointermove', onPointerMove );



// function Animate()
// {
//   requestAnimationFrame(Animate);

//   raycaster.setFromCamera( pointer, camera );

// 	// calculate objects intersecting the picking ray
// 	const intersects = raycaster.intersectObjects( scene.children );

// 	for ( let i = 0; i < intersects.length; i ++ ) {

// 		intersects[ i ].object.material.color.set( 0xff0000 );

// 	}

//   renderer.render(scene, camera)
// }

// Animate();