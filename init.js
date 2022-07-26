
const borneVue=50;//amplitude de deplacement de la camera

let coef = 1;
let x = 18;
let y = 18;
let origine = new THREE.Vector3(0,0,0);
let H2 = new THREE.Vector3(0, 0, 0);
let ptLachee = new THREE.Vector3(-10.9725, 0, 0.125);

let P0 = new THREE.Vector3(-21.0335,0,0);
let P1 = new THREE.Vector3(-9.86,0.76,0);
let P2 = new THREE.Vector3(0,1.29,0);
let P3 = new THREE.Vector3(18,0,0);

let M0 = new THREE.Vector3(-21.0335,0,0);
let M1 = new THREE.Vector3(-21.0335,0,0);
let M2 = new THREE.Vector3(6,4,0);
let M3 = new THREE.Vector3(18,0,0);

var thetap = 0;
var thetapB = 45;
var thetapB1 = 47;
var thetapB2 = 45;
var thetapB3 = 47;
var thetap2 = 0;
var thetap3 = 0;
var pasThetaP3 = 0.25;
var angle = 0
const angleRotationPierre=Math.PI/12;
var s = false;
var b = false;
var n = 1;

let cbeBez;
let cbeBezT;
let cbeBezP;
let cbeBezP2;

let nbPts = 50;
let epaiB = 3;//epaisseur de la courbe de Bezier

var scoreA = 0;
var scoreB = 0;



function init(){
 var stats = initStats();
    // creation de rendu et de la taille
 let rendu = new THREE.WebGLRenderer({ antialias: true });
 rendu.shadowMap.enabled = true;
 let scene = new THREE.Scene();   
 let camera = new THREE.PerspectiveCamera(20, window.innerWidth / window.innerHeight, 0.1, 100);
 rendu.shadowMap.enabled = true;
 rendu.setClearColor(new THREE.Color(0xFFFFFF));
 rendu.setSize(window.innerWidth*.9, window.innerHeight*.9);
 cameraLumiere(scene,camera);
 lumiere(scene);
 //repere(scene);

 var ambientLight = new THREE.AmbientLight( 0x222222);
 scene.add( ambientLight );

 var pointLight = new THREE.PointLight(0x222222);
 camera.add( pointLight );
 scene.add( camera );

 
    var axes = new THREE.AxesHelper(1);    
    scene.add(axes);
    repere(scene);

  const renderer = new THREE.WebGLRenderer();
  renderer.setSize( window.innerWidth, window.innerHeight );
  document.body.appendChild( renderer.domElement );

var controls = new THREE.OrbitControls(camera, rendu.domElement); //contrôles à la souris
  //const controls = new THREE.OrbitControls( camera, renderer.domElement );
    controls.target.set( 0, 0.5, 0 );
    controls.update();
    controls.enablePan = false;
    controls.enableDamping = true;

 //********************************************************
 //
 //  D E B U T    P A R T I E     F O N C T I O N
 //
 //********************************************************
 function tracePt(MaScene, P, CoulHexa, dimPt, bol){
    let sphereGeometry = new THREE.SphereGeometry(dimPt, 12, 24);
    let sphereMaterial = new THREE.MeshBasicMaterial({color: CoulHexa});
    let sphere = new THREE.Mesh(sphereGeometry, sphereMaterial);
    sphere.position.set(P.x, P.y, P.z);
    if (bol) MaScene.add(sphere);
    return sphere;

 }
 function vecteur(MaScene, A, B, CoulHexa, longCone, RayonCone){
    var vecAB = new THREE.Vector3( B.x-A.x, B.y-A.y, B.z-A.z);
    vecAB.normalize();
    MaScene.add( new THREE.ArrowHelper( vecAB, A, B.distanceTo(A), CoulHexa, longCone, RayonCone));
 }

 function repere(MaScene){
    let O = new THREE.Vector3(0, 0, 0);
    let A = new THREE.Vector3(1, 0, 0);
    let B = new THREE.Vector3(0, 1, 0);
    let C = new THREE.Vector3(0, 0, 1);
    let longCone = 0.25;
    let RayonCone = 0.125;
    vecteur(MaScene, O, A, "#FF0000", longCone, RayonCone);
    vecteur(MaScene, O, B, "#00FF00", longCone, RayonCone);
    vecteur(MaScene, O, C, "#0000FF", longCone, RayonCone);

 }

function traceRing(innerRadius, outerRadius, thetaSegments, phiSegments, thetaStart, thetaLength, color, position){
  const geometry = new THREE.RingGeometry( innerRadius, outerRadius, thetaSegments, phiSegments, thetaStart, thetaLength);
  const material = new THREE.MeshPhongMaterial( { color: color, side: THREE.DoubleSide } );
  const mesh = new THREE.Mesh( geometry, material );
  mesh.position.x = position;
  scene.add( mesh );
}

function traceRectangle(width, height, color, positionx){
  const geometry = new THREE.PlaneGeometry( width, height);
  const material = new THREE.MeshPhongMaterial( {color: color} );
  const rectangle = new THREE.Mesh( geometry, material );
  rectangle.position.x = positionx;
  scene.add( rectangle );
}

function segment(MaScene, A, B, CoulHexa, epai){
  var geometry = new THREE.Geometry();
  geometry.vertices.push(A, B);
  let segAB = new THREE.Line(geometry, new THREE.LineBasicMaterial({color: CoulHexa, linewidth: epai}));
  MaScene.add(segAB);
  MaScene.add( new THREE.ArrowHelper( vecAB, A, B.distanceTo(A), CoulHexa));
 }

function traceTore(ptCentre, rayonMaj, rayonMin, nbMeridien, nbParallel, LgArc, colorHexa){
  let geometry = new THREE.TorusGeometry(rayonMaj, rayonMin, nbMeridien, nbParallel, LgArc);
  let material = new THREE.MeshPhongMaterial( { color: colorHexa, side: THREE.DoubleSide} );
  let torus = new THREE.Mesh( geometry, material );
  torus.position.set(ptCentre.x, ptCentre.y, ptCentre.z);
  scene.add(torus);
}

function traceCone(radius, height, positionx, positiony, positionz, color){
  const geometry = new THREE.ConeGeometry(radius, height);
  const material = new THREE.MeshBasicMaterial( {color: color });
  const cone = new THREE.Mesh( geometry, material );
  cone.position.x = positionx;
  cone.position.y = positiony;
  cone.position.z = positionz;
  cone.rotateX(-Math.PI/2);
  return cone;
}

function traceCylindre(radius, radiusBottom, height, radialSegment, color, positionx, positiony, positionz){
  const geometry = new THREE.CylinderGeometry(radius, radiusBottom, height, radialSegment);
  const material = new THREE.MeshBasicMaterial( {color: color });
  const cylindre = new THREE.Mesh( geometry, material );
  cylindre.position.x = positionx;
  cylindre.position.y = positiony;
  cylindre.position.z = positionz;
  cylindre.rotateX(Math.PI/2);
  return cylindre;
}

function TraceBezierCubique(P0, P1, P2, P3, nbPts, coul, epaiCbe){
  let cbeBez = new THREE.CubicBezierCurve3(P0, P1, P2, P3);
  let cbeGeometry = new THREE.Geometry();
  cbeGeometry.vertices = cbeBez.getPoints(nbPts);
  let material2 = new THREE.LineBasicMaterial({color: coul, linewidth: epaiCbe});
  let BezierCubique = new THREE.Line(cbeGeometry, material2)
  return(BezierCubique);
}

function latheBez3(nbePtCbe,nbePtRot,P0,P1,P2,P3,coul,opacite,bolTranspa){
 let p0= new THREE.Vector2(P0.x,P0.y);
 let p1= new THREE.Vector2(P1.x,P1.y);
 let p2= new THREE.Vector2(P2.x,P2.y);
 let p3= new THREE.Vector2(P3.x,P3.y);
 let tabp= new Array(4);
 for (let j=0;j<tabp.length;j++)
   tabp[j]= new THREE.Vector2(0,0);
 tabp[0].copy(p0);tabp[1].copy(p1);
 tabp[2].copy(p2);tabp[3].copy(p3); 
 // points de la courbe de Bezier
 let points = new Array(nbePtCbe+1);
 for(let k=0;k<=(nbePtCbe+1);k++){
   let t2=k/nbePtCbe; 
   t2=t2.toPrecision(50);
   let v0= new THREE.Vector2(0,0);
   v0.addScaledVector(tabp[0],Ber(t2,0,tabp.length-1));
   for(let j=1;j<tabp.length;j++){
     let v1= new THREE.Vector2(0,0);
     v1.addScaledVector(tabp[j],Ber(t2,j,tabp.length-1));
     v0.add(v1);
   }
   points[k] = new THREE.Vector2(v0.x,v0.y);
 }
 let latheGeometry = new THREE.LatheGeometry(points,nbePtRot,0,2*Math.PI); 
 let lathe = surfPhong(latheGeometry,coul,opacite,bolTranspa,"#223322");
 return lathe;
}// fin latheBez3

function stone(CoulHexa){
 let coef = 1;
 let origine = new THREE.Vector3(0,0,0);
 let H0 = new THREE.Vector3(0,0.2,0);
 let H1 = new THREE.Vector3(0.3,0.2,0);
 let H2 = new THREE.Vector3(0.3,0.141,0);
 let H3 = new THREE.Vector3(0.16,0.141,0);
 let P0 = new THREE.Vector3(0,0.141,0);
 let P1 = new THREE.Vector3(0.16,0.141,0);
 let P2 = new THREE.Vector3(0.33,0.2005,0);
 let P3 = new THREE.Vector3(0.33,0.0730,0);
 let M0 = new THREE.Vector3(P3.x,P3.y,0);
 let M1 = new THREE.Vector3(0,0,0);
 let M2 = new THREE.Vector3(0.33,0.1389,0);
 let M3 = new THREE.Vector3(0.33,0.0200,0);
 let I0 = new THREE.Vector3(M3.x,M3.y,0);
 let I1 = new THREE.Vector3(0,0,0);
 let I2 = new THREE.Vector3(0,-0.048,0);
 let I3 = new THREE.Vector3(0,-0.048,0); 
 let vP2P3 = new THREE.Vector3(0,0,0);
 let vTan2 = new THREE.Vector3(0,0,0);

 vP2P3.subVectors(P3,P2);//P3-P2
 vTan2.addScaledVector(vP2P3,coef);
 M1.addVectors(M0,vTan2);

 vP2P3.subVectors(M3,M2);//P3-P2
 vTan2.addScaledVector(vP2P3,coef);
 I1.addVectors(I0,vTan2);

  let nb=100;//nmbre de pts par courbe
  let epai=4;//epaisseur de la courbe
  let nbPtCB=50;//nombre de points sur la courbe de Bezier
  let nbePtRot=150;// nbe de points sur les cercles

  let ptCentre = new THREE.Vector3(-0.06, 0.15,0);
  let geometry = new THREE.TorusGeometry(0.15, 0.025, 20, 20, 3*Math.PI/4);
  let material = new THREE.MeshPhongMaterial( { color: CoulHexa, side: THREE.DoubleSide} );
  let poigne = new THREE.Mesh( geometry, material );
  poigne.position.set(ptCentre.x, ptCentre.y, ptCentre.z);

  let latheP = latheBez3(nbPtCB,nbePtRot,H0,H1,H2,H3,CoulHexa,0.95,false);
  let lathe1 = latheBez3(nbPtCB,nbePtRot,P0,P1,P2,P3,'#7B8183',0.95,false);
  let lathe2 = latheBez3(nbPtCB,nbePtRot,M0,M1,M2,M3,'#999EA0',0.95,false);
  let lathe3 = latheBez3(nbPtCB,nbePtRot,I0,I1,I2,I3,'#7B8183',0.95,false);

  var stone = new THREE.Group();
  stone.add(poigne);
  stone.add(latheP);
  stone.add(lathe1);
  stone.add(lathe2);
  stone.add(lathe3);
  stone.rotateX(Math.PI/2);
  stone.position.z = 0.125;
  stone.position.x = -21.0335;

  return stone;
}

function brush(CoulHexa1, CoulHexa2, CoulHexa3){
  var a = traceRectangle(0.3,1,0.1, CoulHexa2, 0);
  var b = traceCylindre(0.04, 0.04, 2.5, 64, CoulHexa1, 0, 0, 1.251);
  var c = new THREE.Group();
  for(var i = -6; i<= 6; i++){
    for (var j = -23 ;j <= 23; j++) {
      c.add(traceCone(0.02, 0.23, i*0.02, j*0.02, -0.1, CoulHexa3));
    }
  }

  var brush = new THREE.Group();
  brush.add(a);
  brush.add(b);
  brush.add(c);
  brush.position.z = 0.23;
  return brush;
}

function choc(stone1, stone2){
  if(Math.sqrt(Math.pow(stone2.position.x - stone1.position.x, 2) + Math.pow(stone2.position.y - stone1.position.y, 2)) <= 0.7)
    return true;
  
  else
    return false;
}

function stopBrush(stone1, stone2){
  if(Math.sqrt(Math.pow(stone2.position.x - stone1.position.x, 2) + Math.pow(stone2.position.y - stone1.position.y, 2)) <= 4)
    return true;
  else
    return false;
}

function deplacement(stone, t){

  var thetap = 0;
  var angle = 0
  const angleRotationPierre=Math.PI/12;

  let P0 = new THREE.Vector3(-21.0335,0,0);
  let P1 = new THREE.Vector3(-9.86,0.76,0);
  let P2 = new THREE.Vector3(11.33,1.29,0);
  let P3 = new THREE.Vector3(t,1,0);

  cbeBezP = new THREE.CubicBezierCurve(P0, P1, P2, P3);
  
  pointsP = new Array(50);
  for(var i=0; i<50; i++){
    pointsP[i] = cbeBezP.getPoint(i/50);
  }

  if(stone)scene.remove(stone);

  if(thetap<200){
    stone.position.set(pointsP[thetap].x, pointsP[thetap].y, 0.125);
    thetap++
    if(stone.position.x > -10.9725){
      stone.rotateY(angle*angleRotationPierre);
      angle++
    }
    scene.add(stone);
    reAffichage(); 
  }
}

function dansMaison(stone){
  if(Math.sqrt(Math.pow(stone.position.x - 17.3735, 2) + Math.pow(stone.position.y - 0, 2)) <= 1.83)
    return true;
  else
    return false;
}

function laPlusProche(stone1, stone2){
  if(Math.sqrt(Math.pow(stone1.position.x - 17.3735, 2) + Math.pow(stone2.position.y - 0, 2)) < Math.sqrt(Math.pow(stone2.position.x - 17.3735, 2) + Math.pow(stone2.position.y - 0, 2)))
    return 1;
  else
    return 2;
}

function adapt(xPos, new_cbeBez){
  var n = 0;
  for(var i = 0; i<200; i++){
    if(Math.abs(new_cbeBez[i].xPos) < 0.1){
      n = i;
    }
  }
  return n;
}

function score(stone1, stone2, n){
    if(dansMaison(stone1) == true && dansMaison(stone2) == false){
        if(scoreA<n){
          scoreA = scoreA + 1;
      }
    }
    else if(dansMaison(stone1) == false && dansMaison(stone2) == true){
        if(scoreB<n){
          scoreB = scoreB + 1;
      }
    }
    else if(dansMaison(stone1) == true && dansMaison(stone2) == true){
      if(laPlusProche(stone1, stone2) == 1){
        if(scoreA<n){
          scoreA = scoreA + 1;
        }
      }
      else{
        if(scoreB<n){
          scoreB = scoreB + 1;
        }
      }
    }
    else{
      scoreA = scoreA +0;
      scoreB = scoreB +0;
    }
  
    if(scoreA>scoreB){
      document.getElementById("scoreA").innerHTML = scoreA;
      document.getElementById("scoreB").innerHTML = scoreB;
      document.getElementById("scoreA").style.color = "#FC142D";
      document.getElementById("scoreB").style.color = "#FC142D";
    }
    else{
      document.getElementById("scoreA").innerHTML = scoreA;
      document.getElementById("scoreB").innerHTML = scoreB;
      document.getElementById("scoreA").style.color = "#F7F707";
      document.getElementById("scoreB").style.color = "#F7F707";
    }

  }

function launch(tabStoneRouge, tabStoneJaune, n){
    if(stoneRouge[n])scene.remove(stoneRouge[n]);
    if(stoneJaune[n])scene.remove(stoneJaune[n]);
    if(brush)scene.remove(brush);
    if(thetap<200 && thetapB<200 && thetapB1<200){
      stoneRouge[n].position.set(pointsP1[thetap].x, pointsP1[thetap].y, 0.125);
      thetap ++
      if(stoneRouge[n].position.x > -10.9725){
        if(b == false){
          brush.position.set(pointsP1[thetapB].x, pointsP1[thetapB].y, 0.23);
          scene.add(brush);
          b = true;
        }
        else{
          brush.position.set(pointsP1[thetapB1].x, pointsP1[thetapB1].y, 0.23);
          scene.add(brush);
          b = false;
        }
        stoneRouge[n].rotateY(angle*angleRotationPierre);
        angle++
        thetapB++
        thetapB1++
      }
      scene.add(stoneRouge[n]);
      reAffichage();
    }
    else{
      if (choc(stoneRouge[n], stoneJaune[n])==false && s == false){
        if(thetap2<200 && thetapB2<200){
          stoneJaune[n].position.set(pointsP2[thetap2].x, pointsP2[thetap2].y, 0.125);
          thetap2++
          if(stoneJaune[n].position.x > -10.9725){
            if(b == false){
              brush.position.set(pointsP1[thetapB2].x, pointsP1[thetapB2].y, 0.23);
              scene.add(brush);
              b = true;
            }
            else{
              brush.position.set(pointsP1[thetapB3].x, pointsP1[thetapB3].y, 0.23);
              scene.add(brush);
              b = false;
            }
            stoneJaune[n].rotateY(angle*angleRotationPierre);
            thetapB2++
            thetapB3++
            angle++
            if(stopBrush(stoneRouge[n], stoneJaune[n]) == true){
              scene.remove(brush);
            }
          }
          scene.add(stoneJaune[n]);
          scene.add(stoneRouge[n]);
          reAffichage();
        }
      }
      else{
        s = true;
        stoneJaune[n].position.set(pointsP2[thetap2].x, pointsP2[thetap2].y, 0.125);
        scene.add(stoneJaune[n]);
        if (thetap3<3) {
          thetap3 += pasThetaP3;
          stoneRouge[n].position.x+=thetap3; 
          stoneRouge[n].rotateY(angle*angleRotationPierre);
          thetap3++
          angle++
          scene.add(stoneRouge[n]);
          reAffichage();
        }
        else{
          scene.add(stoneRouge[n]);
          scene.add(stoneJaune[n]);
          reAffichage();  
          score(stoneRouge[n], stoneJaune[n], n) ;       
        }
      }
    }
  }

/*function deplacementChoc(stone1, stone2, bool, x, y){
  if (choc(stone1, stone2)==false && s == false){
        if(thetap2<50){
          stone2.position.set(pointsP[thetap2].x, pointsP[thetap2].y, 0.125);
          thetap2++
          if(stone2.position.x > -10.9725){
            stone2.rotateY(angle*angleRotationPierre);
            angle++
          }
          scene.add(stone2);
          scene.add(stone1);
          reAffichage();
        }
      }
      else{
        s = true;
        stone2.position.set(pointsP[thetap2].x, pointsP[thetap2].y, 0.125);
        scene.add(stone2);
        if (thetap3<50) {
          stone1.position.set(pointsP2[thetap3].x, pointsP2[thetap3].y, 0.125);
          stone1.rotateY(angle*angleRotationPierre);
          thetap3++
          angle++
          scene.add(stone1);
          reAffichage();
        }
        else{
          scene.add(stone2);
          scene.add(stone1);
          reAffichage();
        }
}*/

 //********************************************************
 //
 // F I N      P A R T I E     F O N C T I O N
 //
 //********************************************************


 //********************************************************
 //
 //  D E B U T    P A R T I E     G E O M E T R I Q U E
 //
 //********************************************************

//plan du terrain
  const largPlan = 45.720;
  const hautPlan = 4.750;
  const nbSegmentLarg = 30;
  const nbSegmentHaut = 30;
  const PlanSolGeometry = new THREE.PlaneGeometry(largPlan,hautPlan,nbSegmentLarg,nbSegmentHaut);
  const PlanSolMaterial = new THREE.MeshPhongMaterial({color: '#D5EAF3'});
  let PlanSol = new THREE.Mesh(PlanSolGeometry, PlanSolMaterial);
  PlanSol.position.z = -0.0001;
  PlanSol.receiveShadow = true; 
  PlanSol.castShadow = true;
  scene.add(PlanSol);

//traçage de la maison
traceRing(1.23, 1.83, 1000, 1, 0, Math.PI*2, '#E92A0A', 17.3735);
traceRing(0.20, 0.60, 1000, 1, 0, Math.PI*2, '#0A40E9', 17.3735);
traceRing(1.23, 1.83, 1000, 1, 0, Math.PI*2, '#E92A0A', -17.3735);
traceRing(0.20, 0.60, 100000, 1, 0, Math.PI*2, '#0A40E9', -17.3735);

//traçage des lignes du terrain
traceRectangle(0.20, 4.750, '#0A40E9', 19.2035);
traceRectangle(0.02, 4.750, '#000000', 17.3735);
traceRectangle(0.20, 4.750, '#0A40E9', -19.2035);
traceRectangle(0.02, 4.750, '#000000', -17.3735);
traceRectangle(0.20, 4.750, '#E92A0A', 10.9725);
traceRectangle(0.20, 4.750, '#E92A0A', -10.9725);
traceRectangle(21.0335*2, 0.02, '#000000', 0);

//traçage des pierres

let stoneRouge = new Array(5);
for(var i = 0; i <5; i++){
 stoneRouge[i] = stone("#FC142D");
}

let stoneJaune = new Array(5);
for(var i = 0; i <5; i++){
 stoneJaune[i] = stone("#F7F707");
}

var brush = brush("#568FB7", "#101A21", "#101A21");


//courbes de Bézier modélisant le déplaçement des pierres
cbeBezP = new THREE.CubicBezierCurve(P0, P1, P2, P3);
let pointsP = new Array(200);
for(var i=0; i<200; i++){
  pointsP[i] = cbeBezP.getPoint(i/200);
}


cbeBezT = new TraceBezierQuadratique(M0, M1, M3, nbPts,"#0000FF",epaiB);
cbeBez = new THREE.QuadraticBezierCurve3(M0, M2, M3);
 let pointsP1 = new Array(200);
 for(var i=0; i<200; i++){
  pointsP1[i] = cbeBez.getPoint(i/200);
}

let pointsP2 = new Array(200);
 for(var i=0; i<200; i++){
  pointsP2[i] = cbeBez.getPoint(i/200);
}
 //********************************************************
 //
 // F I N      P A R T I E     G E O M E T R I Q U E
 //
 //********************************************************


 //********************************************************
 //
 // D E B U T     P A R T I E     A N I M A T I O N
 //
 //********************************************************

 function reAffichage() {
  setTimeout(function () { 
    //if(n<6){
      //switch(n){
        /*case 1:{*/launch(stoneRouge, stoneJaune, 1);//break;}
        /*case 2:{launch(stoneRouge, stoneJaune, 2);break;}
        case 3:{launch(stoneRouge, stoneJaune, 3);break;}
        case 4:{launch(stoneRouge, stoneJaune, 4);break;}
        case 5:{launch(stoneRouge, stoneJaune, 5);break;}
      }
      n+=1;
    }*/

    
  }, 200);// fin setTimeout(function ()
    // render avec requestAnimationFrame
  rendu.render(scene, camera);
 }// fin fonction reAffichage()

 //********************************************************
 //
 // F I N     P A R T I E     A N I M A T I O N
 //
 //********************************************************


 //********************************************************
 //
 //  D E B U T     M E N U     G U I
 //
 //********************************************************
var gui = new dat.GUI();//interface graphique utilisateur
  // ajout du menu dans le GUI
 let menuGUI = new function () {
   this.cameraxPos = camera.position.x;
   this.camerayPos = camera.position.y;
   this.camerazPos = camera.position.z;
   this.cameraZoom = 1;
   //pb avec camera lockAt
   this.cameraxDir = 0;//camera.getWorldDirection().x;
   this.camerayDir = 0;//camera.getWorldDirection().y;
   this.camerazDir = 0;//camera.getWorldDirection().z;
   this.coefficient=1;
   this.x=1;
   this.y=1;

   //pour actualiser dans la scene   
   this.actualisation = function (){
    posCamera();
    reAffichage();
   }; // fin this.actualisation
 }; // fin de la fonction menuGUI
 // ajout de la camera dans le menu
 ajoutCameraGui(gui,menuGUI,camera);
 //ajout du menu pour actualiser l'affichage 


let guiP1 = gui.addFolder("Trajectoire pierre Rouge");
guiP1.add(menuGUI, "x", 10, 21).onChange(function(){
  M3.x = menuGUI.x;
  if (cbeBezT) scene.remove(cbeBezT);
  cbeBezT = new TraceBezierQuadratique(M0, H2, M3, nbPts,"#0000FF",epaiB);
  cbeBez = new THREE.QuadraticBezierCurve3(M0, H2, M3);
  scene.add(cbeBezT);
});

guiP1.add(menuGUI, "y", -4, 4).onChange(function(){
  M3.y = menuGUI.y;
  if (cbeBezT) scene.remove(cbeBezT);
  cbeBezT = new TraceBezierQuadratique(M0, H2, M3, nbPts,"#0000FF",epaiB);
  cbeBez = new THREE.QuadraticBezierCurve3(M0, H2, M3);
  scene.add(cbeBezT);
});


guiP1.add(menuGUI, "coefficient", -2, 1).onChange(function(){
  let xPos1 = pointsP1[thetap].x;
  let vMmM0 = new THREE.Vector3(0, 0, 0);
  let vTan1 = new THREE.Vector3(0, 0, 0);
  vMmM0.subVectors(M0, ptLachee);
  vTan1.addScaledVector(vMmM0, menuGUI.coefficient);
  H2.addVectors(vTan1, M2);
  if (cbeBezT) scene.remove(cbeBezT);
  //if (stone1) scene.remove(stone1);
  cbeBezT = new TraceBezierQuadratique(M0, H2, M3, nbPts,"#0000FF",epaiB);
  cbeBez = new THREE.QuadraticBezierCurve3(M0, H2, M3);
  for(var i=0; i<200; i++){
    pointsP1[i] = cbeBez.getPoint(i/200);
  }
  thetap = adapt(xPos1, pointsP1);
  scene.add(cbeBezT);

});

let guiP2 = gui.addFolder("Trajectoire pierre Jaune");
guiP2.add(menuGUI, "x", 10, 21).onChange(function(){
  M3.x = menuGUI.x;
  if (cbeBezT) scene.remove(cbeBezT);
  cbeBezT = new TraceBezierQuadratique(M0, H2, M3, nbPts,"#0000FF",epaiB);
  cbeBez = new THREE.QuadraticBezierCurve3(M0, H2, M3);
  scene.add(cbeBezT);
});

guiP2.add(menuGUI, "y", -4, 4).onChange(function(){
  M3.y = menuGUI.y;
  if (cbeBezT) scene.remove(cbeBezT);
  cbeBezT = new TraceBezierQuadratique(M0, H2, M3, nbPts,"#0000FF",epaiB);
  cbeBez = new THREE.QuadraticBezierCurve3(M0, H2, M3);
  scene.add(cbeBezT);
});

guiP2.add(menuGUI, "coefficient", -2, 1).onChange(function(){
  let xPos2 = pointsP2[thetap2].x;
  let vMmM0 = new THREE.Vector3(0, 0, 0);
  let vTan1 = new THREE.Vector3(0, 0, 0);
  vMmM0.subVectors(M0, ptLachee);
  vTan1.addScaledVector(vMmM0, menuGUI.coefficient);
  H2.addVectors(vTan1, M2);
  if (cbeBezT) scene.remove(cbeBezT);
  //if (stone1) scene.remove(stone1);
  cbeBezT = new TraceBezierQuadratique(M0, H2, M3, nbPts,"#0000FF",epaiB);
  cbeBez = new THREE.QuadraticBezierCurve3(M0, H2, M3);
  for(var i=0; i<200; i++){
    pointsP2[i] = cbeBez.getPoint(i/200);
  }
  thetap2 = adapt(xPos2, pointsP2);
  scene.add(cbeBezT);

});

 gui.add(menuGUI, "actualisation");
 menuGUI.actualisation();
 //********************************************************
 //
 //  F I N     M E N U     G U I
 //
 //********************************************************
 renduAnim();
 
  // definition des fonctions idoines
 function posCamera(){
  camera.position.set(menuGUI.cameraxPos*testZero(menuGUI.cameraZoom),menuGUI.camerayPos*testZero(menuGUI.cameraZoom),menuGUI.camerazPos*testZero(menuGUI.cameraZoom));
  camera.lookAt(menuGUI.cameraxDir,menuGUI.camerayDir,menuGUI.camerazDir);
  actuaPosCameraHTML();
 }
 
 //affichage dans la page HTML
 function actuaPosCameraHTML(){
  document.forms["controle"].PosX.value=testZero(menuGUI.cameraxPos);
  document.forms["controle"].PosY.value=testZero(menuGUI.camerayPos);
  document.forms["controle"].PosZ.value=testZero(menuGUI.camerazPos); 
  document.forms["controle"].DirX.value=testZero(menuGUI.cameraxDir);
  document.forms["controle"].DirY.value=testZero(menuGUI.camerayDir);
  document.forms["controle"].DirZ.value=testZero(menuGUI.camerazDir);
 } // fin fonction posCamera
  // ajoute le rendu dans l'element HTML
 renduAnim();
 
 
  // ajoute le rendu dans l'element HTML
 document.getElementById("webgl").appendChild(rendu.domElement);
   
  // affichage de la scene
 rendu.render(scene, camera);
  
 /*function reAffichage() {
  setTimeout(function () {
    if(stone1)scene.remove(stone1);
    deplacement(stone1, 3, 1);

  }, 200);// fin setTimeout(function ()
    // rendu avec requestAnimationFrame
  rendu.render(scene, camera);
 }// fin fonction reAffichage()*/
 
 
  function renduAnim() {
    stats.update();
    // render avec requestAnimationFrame
    requestAnimationFrame(renduAnim);
// ajoute le rendu dans l'element HTML
    rendu.render(scene, camera);
  }
 
 }// fin fonction init()