void eepromClear(){
  for (int i=0 ;i< 250; i++){
    EEPROM.write(i,0);
  }
}


void calculatePath(boolean runningNext){
  floodFill2();
  
  byte xprevious=x;
  byte yprevious=y;
  x=0;
  y=0;
  byte oldOrient= orient;
  orient=0;
  
  cellCount=0;
  
    while(flood2[y][x]!=1){
        toMove2();
        //pathQueue.push(dir);

        
        if (runningNext== true){
        pathQueue.push(dir);
        }
        
        //Serial2.println(dir);
    
        if (dir=='L'){
            orient = orientation(orient,'L');
        }

        else if (dir=='R'){
            orient = orientation(orient,'R');
        }

        else if (dir=='B'){
            orient = orientation(orient,'L');
            orient = orientation(orient,'L');
        }

        
        xprev=x;
        yprev=y;
        updateCoordinates();
        
        
  }

        
        x= xprevious;
        y= yprevious;
        orient=oldOrient;   
        buzz();
}


void traverse(byte xdes, byte ydes, boolean middleSquare, boolean shortPath, boolean smooth){

  byte currentx= x;
  byte currenty= y;
  
  if (shortPath== false){
    
  appendDestination(xdes,ydes,middleSquare);
  floodFill3();
  checkWallsCell();
  updateWalls(x, y, orient, L, R, F);
  
  while(flood[y][x]!=0){
    Serial2.println();
    Serial2.print("x : ");
    Serial2.print(x);
    Serial2.print(", y : ");
    Serial2.println(y);
    
    checkWallsCell();
    updateWalls(x, y, orient, L, R, F);
    appendDestination(xdes,ydes,middleSquare);
    floodFill3();
    dir= toMove(x,y,xprev,yprev,orient);

    Serial2.print("toMove() : ");
    Serial2.println(dir);

    
        if (dir=='L'){
            orient = orientation(orient,'L');
            if(x==0 || x== currentx){
              if(y==0 || y== currenty){
                leftAboutTurn();
                delay(500);
                cellStart();
                currentx=0;
                currenty=0;
              }
              else{
                leftTurn();
              }
            }
            else{
            leftTurn();}
        }

        else if (dir=='R'){
          orient = orientation(orient,'R');
            if(x==0 || x== currentx){
              if(y==0 || y== currenty){
                rightAboutTurn();
                delay(500);
                cellStart();
                currentx=0;
                currenty=0;
              }
              else{
                rightTurn();
              }
            }
            else{
            rightTurn();}
        }

        else if (dir=='B'){
            orient = orientation(orient,'L');
            orient = orientation(orient,'L');
            if((x==0 && y==0)||(x== currentx && y== currenty)){
              turnBack();
              delay(500);
              cellStart();
              currentx=0;
                currenty=0;
              }
              else{
              cellBack();
              }
        }
        else{
          if((x==0 && y==0)||(x== currentx && y== currenty)){
            cellStart();
            currentx=0;
                currenty=0;
          }
          else{
          cellForward();
          }
        }
        xprev=x;
        yprev=y;
        updateCoordinates();
  }
  }

  else{

        F= false;
        R= false;
        L= false;

    if (smooth == true){
        calculatePath(true);
    
        while (!pathQueue.isEmpty ()){

        dir= pathQueue.pop();

        if (dir=='L'){
            orient = orientation(orient,'L');
            if((x==0 && y==0)||(x== currentx && y== currenty)){
              leftAboutTurn();
              delay(500);
              cellStart();
              currentx=0;
              currenty=0;
            }
            else{
            leftSmoothTurn();}
            
        }

        else if (dir=='R'){
            orient = orientation(orient,'R');
            if((x==0 && y==0)||(x== currentx && y== currenty)){
              rightAboutTurn();
              delay(500);
              cellStart();
              currentx=0;
              currenty=0;
            }
            else{
            rightSmoothTurn();}
        }

        else if (dir=='B'){
            orient = orientation(orient,'L');
            orient = orientation(orient,'L');
            if((x==0 && y==0)||(x== currentx && y== currenty)){
              turnBack();
              delay(500);
              cellStart();
              currentx=0;
              currenty=0;
            }
            else{
            cellBack();}
          }
        
        else{
          if((x==0 && y==0)||(x== currentx && y== currenty)){
              cellStart();
              currentx=0;
              currenty=0;
            }
            else{
            cellForward();}
          }

          xprev=x;
          yprev=y;
          updateCoordinates();
        
      }

      
    }

    else{
      
    calculatePath(true);
    
    while (!pathQueue.isEmpty ()){
    checkWallsCell();
    dir= pathQueue.pop();
    
        if (dir=='L'){
            orient = orientation(orient,'L');
            if((x==0 && y==0)){
              leftAboutTurn();
              delay(500);
              cellStart();
            }
            else{
            leftTurn();}
            
        }

        else if (dir=='R'){
            orient = orientation(orient,'R');
            if((x==0 && y==0)){
              rightAboutTurn();
              delay(500);
              cellStart();
            }
            else{
            rightTurn();}
        }

        else if (dir=='B'){
            orient = orientation(orient,'L');
            orient = orientation(orient,'L');
            if((x==0 && y==0)){
              turnBack();
              delay(500);
              cellStart();
            }
            else{
            cellBack();}
          }
        
        else{
          if((x==0 && y==0)){
              cellStart();
            }
            else{
            cellForward();}
          }

          xprev=x;
          yprev=y;
          updateCoordinates();
          
        }   
    }
  }
  }


void fixOrientation(){
  while(orient!=0){
    leftAboutTurn();
    orient = orientation(orient,'L');
    delay(500);
  }
}

void loadCells(){
  for (int i=0;i<14;i++){
    for (int j=0; j<14;j++){
      cells[j][i]= EEPROM.read(i*14+j);
    }
  }
}

void writeCells(){
  for (int i=0;i<14;i++){
    for (int j=0; j<14;j++){
      EEPROM.write(i*14+j ,cells[j][i]);
    }
  }
}


void searchStates(){
      mazeStart();
      
      traverse(0,0,true,false,false);
      L= false; R= false; F= false;
      center();
      cellBrake();
      buzz();
      delay(3000);
      traverse(15,0,false,false,false);
      cellBrake();
      buzz();
      traverse(0,0,false,false,false);
      cellBrake();
      fixOrientation();
      delay(3000);
      
      // mazeStart();

      // traverse(0,0,true,true,false);
      // L= false; R= false; F= false;
      // center();
      // cellBrake();
      // buzz();
      // delay(3000);
      // traverse(0,0,false,false,false);
      // cellBrake();
      // buzz();
      // fixOrientation();
      // delay(3000);

      // mazeStart();

      // traverse(0,0,true,true,true);
      // L= false; R= false; F= false;
      // center();
      // cellBrake();
      // buzz();
      // delay(3000);
      // traverse(0,0,false,false,false);
      // cellBrake();
      // buzz();
      // fixOrientation();
      // delay(3000);
}


