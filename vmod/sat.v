module sat ( input signed [18:0] iData,
	         output signed [15:0] oData);

assign oData = (-32768 >= iData) ? -32768 :
	       (32767 <= iData) ? 32767: iData;
endmodule
