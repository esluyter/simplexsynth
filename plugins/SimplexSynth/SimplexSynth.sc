SimplexSynth : UGen {
	*ar { |freq=100, offsetX=0, offsetY=0, radius=2, oct=3, syncSig=(DC.ar(0)), iphase=0|
		/*
		var phase = Phasor.ar(syncSig, SampleDur.ir * freq) * 2pi;
	  ^this.ar2(
	    SinOsc.ar(0, (phase + (pi/2))) * freqScale + offsetX,
	    SinOsc.ar(0, phase) * freqScale + offsetY,
	    oct
	  );
		*/
		^this.multiNew('audio', freq, offsetX, offsetY, radius, oct, syncSig, iphase.wrap(0, 2pi));
	}

	/*
	*ar2 { |x=0, y=0, oct=3|
		^this.multiNew('audio', x, y, max(1, oct));
	}
	*/

	checkInputs {
		/* TODO */
		^this.checkValidInputs;
	}
}
