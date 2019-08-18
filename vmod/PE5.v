module PE5 #(parameter BW1=16, BW2=19)
	     (input iCLK, iRSTn,
	      input signed [7:0] iW1,iW2,iW3,iW4,iW5,
	      input signed [7:0] iX,
	      input signed [BW1-1:0] iPsum,
	      output signed [BW2-1:0] oPsum);

wire signed[16:0] oPsum1,oPsum2;
wire signed[17:0]  oPsum3, oPsum4;



PE #(16,17)fa1(.iCLK(iCLK),.iRSTn(iRSTn),.iW(iW1),.iX(iX),.iPsum(iPsum),.oPsum(oPsum1));
PE #(17,17)fa2(.iCLK(iCLK),.iRSTn(iRSTn),.iW(iW2),.iX(iX),.iPsum(oPsum1),.oPsum(oPsum2));
PE #(17,18)fa3(.iCLK(iCLK),.iRSTn(iRSTn),.iW(iW3),.iX(iX),.iPsum(oPsum2),.oPsum(oPsum3));
PE #(18,18)fa4(.iCLK(iCLK),.iRSTn(iRSTn),.iW(iW4),.iX(iX),.iPsum(oPsum3),.oPsum(oPsum4));
PE #(18,19)fa5(.iCLK(iCLK),.iRSTn(iRSTn),.iW(iW5),.iX(iX),.iPsum(oPsum4),.oPsum(oPsum));

endmodule
