module delay #(parameter N=16, D=26)
	      (input iCLK, iRSTn,
	       input [N-1:0] iData,
	       output [N-1:0] oData );

wire [N-1:0] data_arr[0:D];

assign data_arr[0] = iData;
genvar i;
generate for (i=0;i<D;i=i+1) begin: gen_dff
dff#(N) u_dff(.iCLK(iCLK), .iRSTn(iRSTn), .iData(data_arr[i]), .oData(data_arr[i+1]));
			     end
endgenerate

assign oData = data_arr[26];

endmodule
