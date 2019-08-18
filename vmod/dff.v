module dff #(parameter N=16, D=26)
			( input iCLK, iRSTn, 
		     	  input signed [N-1:0] iData,
			 output reg signed[N-1:0] oData );

always@(posedge iCLK, negedge iRSTn)
begin
	if(!iRSTn)
	oData <=0;
	else 
	oData <= iData;
end
endmodule
