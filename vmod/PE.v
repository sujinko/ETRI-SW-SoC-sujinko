module PE #(parameter BW1=16, BW2=16)
	   (input iCLK, iRSTn,
	    input signed [7:0] iW,
	    input signed [7:0] iX,
	    input signed [BW1-1:0] iPsum,
	    output reg signed [BW2-1:0] oPsum);


always@(posedge iCLK, negedge iRSTn)
begin
	if(!iRSTn)
	oPsum <=0;
	else 
	oPsum <= iW * iX + iPsum;
end
endmodule



