SimplexSynth : UGen {
	*ar { |freq=100, offsetX=0, offsetY=0, freqScale=2, oct=3, syncSig=0|
		var phase = Phasor.ar(syncSig, SampleDur.ir * freq) * 2pi;
	  ^this.ar2(
	    SinOsc.ar(0, (phase + (pi/2))) * freqScale + offsetX,
	    SinOsc.ar(0, phase) * freqScale + offsetY,
	    oct
	  );
	}
	
	*ar2 { |x=0, y=0, oct=3|
		^this.multiNew('audio', x, y, max(1, oct));
	}

	checkInputs {
		/* TODO */
		^this.checkValidInputs;
	}
}
