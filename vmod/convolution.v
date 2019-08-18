module convolution #(parameter BW1=16, BW2=16)
	    (input iCLK, iRSTn,iWren,
             input signed [7:0] iX,
	     input [7:0] iWeight,
	     input [4:0] iADDR,
	     output signed [BW2-1:0] oPsum);


wire signed [7:0]iW1,iW2,iW3,iW4,iW5,iW6,iW7,iW8,iW9,iW10,iW11,iW12,iW13,iW14,iW15,iW16,iW17,iW18,iW19,iW20,iW21,iW22,iW23,iW24,iW25;
wire signed [18:0] a1,a4,a7,a10,a13;
wire signed [15:0] a2,a3,a5,a6,a8,a9,a11,a12;

reg [7:0] x0;


always@(posedge iCLK, negedge iRSTn)
begin
	if(!iRSTn)
	x0 <=0;
	else 
	x0 <= iX;
end

regist re1 (.iCLK(iCLK), .iRSTn(iRSTn), .iWren(iWren),.iWeight(iWeight),.iAddr(iADDR) ,.iW1(iW1),.iW2(iW2),.iW3(iW3),.iW4(iW4),.iW5(iW5),.iW6(iW6),.iW7(iW7),.iW8(iW8),.iW9(iW9),.iW10(iW10),.iW11(iW11),.iW12(iW12),.iW13(iW13),.iW14(iW14),.iW15(iW15),.iW16(iW16),.iW17(iW17),.iW18(iW18),.iW19(iW19),.iW20(iW20),.iW21(iW21),.iW22(iW22),.iW23(iW23),.iW24(iW24),.iW25(iW25));

PE5   #(16,19)st1 (.iCLK(iCLK),.iRSTn(iRSTn),.iW1(iW1),.iW2(iW2),.iW3(iW3),.iW4(iW4),.iW5(iW5),.iX(x0),.iPsum(0),.oPsum(a1));
sat   st2 (.iData(a1), .oData(a2));
delay st3 (.iCLK(iCLK),.iRSTn(iRSTn), .iData(a2), .oData(a3));

PE5   #(16,19)nd1 (.iCLK(iCLK),.iRSTn(iRSTn),.iW1(iW6),.iW2(iW7),.iW3(iW8),.iW4(iW9),.iW5(iW10),.iX(x0),.iPsum(a3),.oPsum(a4));
sat   nd2 (.iData(a4), .oData(a5));
delay nd3 (.iCLK(iCLK),.iRSTn(iRSTn), .iData(a5), .oData(a6));

PE5   #(16,19)rd1 (.iCLK(iCLK),.iRSTn(iRSTn),.iW1(iW11),.iW2(iW12),.iW3(iW13),.iW4(iW14),.iW5(iW15),.iX(x0),.iPsum(a6),.oPsum(a7));
sat   rd2 (.iData(a7), .oData(a8));
delay rd3 (.iCLK(iCLK),.iRSTn(iRSTn), .iData(a8), .oData(a9));

PE5   #(16,19)th1 (.iCLK(iCLK),.iRSTn(iRSTn),.iW1(iW16),.iW2(iW17),.iW3(iW18),.iW4(iW19),.iW5(iW20),.iX(x0),.iPsum(a9),.oPsum(a10));
sat   th2 (.iData(a10), .oData(a11));
delay th3 (.iCLK(iCLK),.iRSTn(iRSTn), .iData(a11), .oData(a12));

PE5   #(16,19)fi1 (.iCLK(iCLK),.iRSTn(iRSTn),.iW1(iW21),.iW2(iW22),.iW3(iW23),.iW4(iW24),.iW5(iW25),.iX(x0),.iPsum(a12),.oPsum(a13));
sat   fi2 (.iData(a13), .oData(oPsum));



endmodule
