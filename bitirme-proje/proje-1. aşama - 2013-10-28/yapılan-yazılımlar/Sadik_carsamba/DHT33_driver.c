UINT8 nem_oku()
{
	unsigned char i, bit_time, bit_temp, lowda_bekle, highda_bekle;

	sensor_start();

	RE1 = 0; TRISE1 = 0;//bir pini output yapýyoruz
	__delay_ms( 3000 ); // 3ms
	TRISE1 = 1; // 1-wire bir yapýlýr,//sonra input yapýyoruz
	NOP();
	NOP();
	NOP();
	NOP();
	NOP();
	NOP();
	NOP();
	NOP();
	NOP();
	NOP();
	NOP();
	NOP();
	NOP();
	NOP();
	NOP();
	NOP();
	NOP();
	NOP();
	NOP();
	NOP();

	if(RE1 == 0) {sensor_durum = SENSOR_YOK; sensor_end(); return sensor_durum;}//Burada sensor durum burada sýfýr olur

	highda_bekle = 0;
	while(RE1 == 1) {
		highda_bekle++;
		if(highda_bekle >=250) {
			sensor_durum = SENSORDE_HATA_H1;
			sensor_end();
			return sensor_durum;
		} // no response from sensor
	}

	lowda_bekle = 0;
	while(RE1 == 0) {
		lowda_bekle++;
		if(lowda_bekle >=250) {
			sensor_durum = SENSORDE_HATA_L1;
			sensor_end();
			return sensor_durum;
		} // too long low state, ERROR
	}

	highda_bekle = 0;
	while(RE1 == 1) {
		highda_bekle++;
		if(highda_bekle >=250) {
			sensor_durum = SENSORDE_HATA_H2;
			sensor_end();
			return sensor_durum;
		} // too long high state, ERROR
	}

	for(i=0; i<40; i++) {
		bit_time = 0;
		lowda_bekle = 0;
		while(RE1==0) {
			lowda_bekle++;
			if(lowda_bekle > 250) {
				sensor_durum = SENSORDE_HATA_H2 + 1 + i;
				sensor_end();
				return sensor_durum;
			}
		} // low iken bekle

		while(RE1==1)  {
			bit_time++;
			if(bit_time>250){
				sensor_durum = SENSORDE_HATA_H2 + 50 + i;
				sensor_end();
				return sensor_durum;
			}
		} // sureyi olc

		//if(i>=20) dene[i-20] = bit_time;
		if (bit_time > 50) bit_temp = 1; else bit_temp = 0;
		nem[i/8] = (nem[i/8] << 1) | bit_temp;
	}

	//if(sensor_durum == SENSOR_YOK) {nem[0]=0xFF; nem[1]=0xFF; nem[2]=0xFF; nem[3]=0xFF;}

	if((UINT8) (nem[0]+nem[1]+nem[2]+nem[3]) == nem[4]) { // CHKSUM tutuyorsa
		nem_deger = (nem[0] << 8) + nem[1];
		sicaklik_deger = (nem[2] << 8) + nem[3];
		if(sicaklik_deger & 0x8000UL) {
			sicaklik_deger = sicaklik_deger & 0x7FFFUL;
			eksi = 1;
		} else eksi = 0;
	} else sensor_durum = SENSOR_CHKSUM_HATASI;		// CHKSUM tutMUyorsa

	sensor_end();
	return sensor_durum; // her sey normal ise 0 dondur
}

void sensor_start(void) {
	UINT8 i;

	TRISE1 = 1;//Ýnput ayný pini
	__delay_ms(1000);

	RD5 = 1;    // nem sensorune guc ver
	TRISD5 = 0; // RD5 output/7Bir pini output yapýp high yapýyoruz

	for(i=0; i<4; i++) {
		while(!WA); P3 = 0; P6 = 0;
		__delay_ms(500); // sensor kendisini 2sn icinde topluyor!
		while(!WA); P3 = 1; P6 = 1;
		__delay_ms(500); // sensor kendisini 2sn icinde topluyor!
	}

	OSCCONbits.SCS = 0b00; 	// 00 = Clock determined by FOSC<2:0> in Configuration Word 1. (32MHz icin 00 olmali)
	// 01 = Timer1 oscillator
	// 1x = Internal oscillator block
	OSCCONbits.IRCF = 0b1110; // 1101 -> 4MHz, 1100 -> 2MHz, 1011 -> 1MHz, 0111 -> 500kHz, 1110 = 8 MHz or 32 MHz HF
	SPLLEN = 1; // 1 = 4x PLL Is enabled, (If PLLEN in Configuration Word 1 = 0:)

	__delay_ms( 100 ); // EK SURE

	sensor_durum = 0;
}

void sensor_end(void) {

	OSCCONbits.SCS = 0b01; 	// 00 = Clock determined by FOSC<2:0> in Configuration Word 1. (32MHz icin 00 olmali)
	// 01 = Timer1 oscillator
	// 1x = Internal oscillator block
	SPLLEN = 0;

	__delay_ms( 30 ); // EK SURE

	RD5 = 0;    // nem sensorune guc ver
	TRISD5 = 0; // RD5 output
	RE1 = 0;
	TRISE1 = 0;

	__delay_ms( 30 ); // EK SURE
}