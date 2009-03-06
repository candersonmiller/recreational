// sound file
Hid hi;
HidMsg msg;
 
 
 
adc => FFT fft =^ Centroid cent => blackhole;
 
 
//which keyboard
0 => int device;
 
 
 
///All of this is for OSC sending
"localhost" => string hostname;
9001 => int port;
 
// send object
OscSend xmit;
 
xmit.setHost( hostname, port );
 
 
//"/Users/andersonmiller/Music/Soulmachine.wav" => string filename;
//if( me.args() ){
//  me.arg(0) => filename;
//  me.arg(1) => Std.atoi => device;
//}
 
 
// open keyboard (get device number from command line)
if( !hi.openKeyboard( device ) ) me.exit();
<<< "keyboard '" + hi.name() + "' ready", "" >>>;
 
 
//SndBuf buf => dac;
// load the file
//filename => buf.read;
adc => dac;
 
// for the pause state variable
1 => int running;
 
 
//set parameters
512 => fft.size;
 
// compute srate
second / samp => float srate;
 
fun void print_centroid(){
  // upchuck: take fft then centroid
    cent.upchuck();
    // print out centroid
  cent.fval(0) * srate / 2 => float centroid;
    //<<< centroid >>>;
  fft.size()::samp => now;
  xmit.startMsg( "/bounce", "f" );
  centroid=> xmit.addFloat;
  
  me.yield();
}
 
fun void print_fft(){
  complex c[];
  UAnaBlob blob;
  fft.upchuck() @=> blob; // store the result in blob.
  blob.fvals() @=> float mag_spec[]; // get the magnitude spectrum as float array
  blob.cvals() @=> complex spec[]; // get the whole spectrum as complex array
  mag_spec[0] => float first_mag; // get the first bin of the magnitude spectrum
  mag_spec[1] => float second_mag;
  mag_spec[2] => float third_mag;
  mag_spec[3] => float fourth_mag;
  mag_spec[4] => float fifth_mag;
  mag_spec[5] => float sixth_mag;
  mag_spec[6] => float seventh_mag;
  mag_spec[7] => float eighth_mag;
  mag_spec[8] => float ninth_mag;
  mag_spec[9] => float tenth_mag;
  mag_spec[10] => float eleventh;
  mag_spec[11] => float twelfth;
  mag_spec[12] => float thirteenth;
  mag_spec[13] => float fourteenth;
  mag_spec[14] => float fifteenth;
  blob.fval(0) => float first_mag2; // equivalent way to get first bin of mag spectrum
  fft.upchuck().fval(0) => float first_mag3; // yet another equivalent way
  fft.upchuck().cval(0) => complex first_spec; // similarly, get 1st spectrum bin
  
  xmit.startMsg("/fft", "fffffffffffffff");
  first_mag => xmit.addFloat;
  second_mag => xmit.addFloat;
  third_mag => xmit.addFloat;
  fourth_mag => xmit.addFloat;
  fifth_mag => xmit.addFloat;
  sixth_mag => xmit.addFloat;
  seventh_mag => xmit.addFloat;
  eighth_mag => xmit.addFloat;
  ninth_mag => xmit.addFloat;
  tenth_mag => xmit.addFloat;
  eleventh => xmit.addFloat;
  twelfth => xmit.addFloat;
  thirteenth => xmit.addFloat;
  fourteenth => xmit.addFloat;
  fifteenth => xmit.addFloat;
  //<<< c[0]$polar, c[1]$polar,
  // c[2]$polar, c[3]$polar >>>;
  
  me.yield();
}
 
fun void pause(){
  //hi => now;
 
  100::ms => now;
}
 
//spork ~ print_centroid() @=> Shred cf;
//me.yield();
 
//spork ~ pause() @=> Shred cf1;
//me.yield();
 
 
 
 
 
 
// time loop
while( true )
{
  
  print_centroid();
  print_fft();
  if(hi.recv( msg )){
       if( msg.isButtonDown() )
      {
      if(msg.ascii == 80){
            <<< "oh shit I implemented a pause button" >>>;
        if(running){
          0 => running;
          //0 => buf.rate;
        }
        else{
          1 => running;
          //1 => buf.rate;
        }
      }
 
    }
  }
    1::ms => now;
  
}
 
