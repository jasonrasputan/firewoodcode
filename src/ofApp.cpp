#include "ofApp.h"

	
//--------------------------------------------------------------
void ofApp::setup(){
	ofSetVerticalSync(true);
	
	ringButton.addListener(this,&ofApp::ringButtonPressed);
 

	gui.setup("panel"); // most of the time you don't need a name but don't forget to call setup
	gui.add(ringButton.setup("ring"));
	
	
	bHide = true;
   
	ring.loadSound("bass.mp3");
    ofSetFrameRate( 15 ) ;
    bNoteAdded = false ;
    bStillPressing = false ;
   xml.load( "data.xml" )  ;
    xml.setTo("notes") ;
    currentNote = 0 ;
    
    int numNotes = xml.getNumChildren() ;
    if ( numNotes > 0 )
    {
   
    //for ( int i  = numNotes.size()-1 ; i > 0  ; i-- )
       for ( int i  = 0; i < numNotes  ; i++ )
        {
            DateTime dt ;
            string branch = "note[" + ofToString( i ) + "]" ;
            dt.hour =  xml.getValue<int>(branch+"hours") ;
            dt.minute =  xml.getValue<int>(branch+"minutes") ;
            dt.second =  xml.getValue<int>(branch+"seconds") ;
            dt.value = xml.getValue<int>(branch+"value") ;
           
            
            int totalSeconds = 0 ;
            totalSeconds = dt.hour * 60 * 60 ;
            totalSeconds += dt.minute * 60 ;
            totalSeconds += dt.second ;
            
            
            
            notes.push_back( dt ) ;
            //int selectedIndex = ofMap( totalSeconds , 0 , secondsInDay , 0 , numFrames, true ) ;
            //frames[ selectedIndex ] = true ;
            
            ofLogNotice() << " note [ " << i << " ] is : " << dt.toString() << " selected Index is :" << 0 ;  ;
       
        }
        
        
    }
    else
    {
        
    }
    
    
    lastTime == -1 ; 
    
    
}

//--------------------------------------------------------------
void ofApp::exit(){
	ringButton.removeListener(this,&ofApp::ringButtonPressed);
}

//--------------------------------------------------------------


//--------------------------------------------------------------
void ofApp::ringButtonPressed(){
	
    
}

//-------------------------------------------------------------

//--------------------------------------------------------------
void ofApp::update(){
    

    
    
    /*
    if ( ofGetMousePressed() && frames[currentFrame]== true )
    {
        
        ring.play();
    }*/

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackgroundGradient(ofColor::white, ofColor::gray);
    
    
/* if ( frames[currentFrame]== true )
 {
     
     ring.play();
 }*/
    
    float maxWidth = 40 ;
    
    if ( notes.size() > 0 )
    {
    float w = ofGetWidth() / notes.size() ;
    if ( w > maxWidth )
        w = maxWidth ;
    
    
    for (int i = 0; i < notes.size() ; i++)
    {
        if ( i == currentNote )
            ofSetColor( 0 , 255 , 0 ) ;
        else
            ofSetColor( 255 ) ;
        int valueY = ofMap( notes[i].value , 0.0f , 4.0f , 0 , ofGetHeight() ) ;
        ofRect( i * w ,valueY ,  w , 15 ) ;
        
    }
        
        
    }
    
    
    //ofSetColor( ofColor::yellow ) ;
    //ofRect( w * currentFrame , 75 , w , 10 ) ;
    gui.draw();
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    int note = -1 ;
    
	switch ( key )
    {
       case 'A':
       case 'a':
            note = 0 ;
            break ;
            
        case 's':
        case 'S':
            note = 1 ;
            break ;
            
        case 'd':
        case 'D':
            note = 2 ;
            break ;
            
        case 'f':
        case 'F':
            note = 3 ;
            break ;
            
        case 'g':
        case 'G':
            note = 4 ;
            break ;
            
            
        case 'c':
        case 'C':
            xml.clear() ;
            notes.clear() ;
            xml.save( "data.xml" ) ;
            break ;
            
    }
    if ( note != -1 )
    {
        if ( bNoteAdded == false )
        {
            bNoteAdded = true ;
            ofXml noteXml ;
            noteXml.addChild("note" ) ;
            noteXml.setTo("note") ;
            //noteXml.setTo("note[" + ofToString( tagId ) + "]" ) ;
            noteXml.addValue( "hours" , ofGetHours() ) ;
            noteXml.addValue( "minutes" , ofGetMinutes() ) ;
            noteXml.addValue( "seconds" , ofGetSeconds() ) ;
            noteXml.addValue( "value" , note ) ;
            xml.setTo("notes") ;
            xml.addXml( noteXml ) ;
         
            xml.save( "data.xml" ) ;
            
            
            DateTime dt ;
            dt.hour = ofGetHours() ;
            dt.minute = ofGetMinutes() ;
            dt.second = ofGetSeconds() ;
            dt.value = note ;
            notes.push_back( dt ) ;
            currentNote = notes.size() - 1 ;
        }
        else
        {
            bStillPressing = true ;
            if ( ( lastTime + duration ) < ofGetSystemTime() )
            {
                DateTime dt = notes[ currentNote ] ;
                switch( dt.value )
                {
                    case 0 :
                        ring.setSpeed( 0.75f );
                        break ;
                        
                    case 1 :
                        ring.setSpeed( 0.92 ) ;
                        break ;
                        
                    case 2 :
                        ring.setSpeed( 1.0f ) ;
                        break ;
                        
                    case 3 :
                        ring.setSpeed( 1.12 ) ;
                        break ;
                        
                    case 4:
                        ring.setSpeed( 1.25 ) ;
                        break ;
                }
                ring.play() ;
                currentNote-- ;
                if ( currentNote < 0 )
                    currentNote = 0 ; 
                duration = 500 ;
                lastTime = ofGetSystemTime() ;
            }
        }
     }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	bStillPressing = false ;
    bNoteAdded = false ;
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
	
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
   
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{
	//ring.play();
    
   // frames[currentFrame] = true;
    
    
    //int tagId = xml.addChild( "note" ) ;
    
    
   
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
   
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
	
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 
	
}
