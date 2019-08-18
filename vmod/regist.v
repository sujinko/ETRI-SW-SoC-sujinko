module regist (input iCLK,iRSTn,iWren,
               input [7:0] iWeight,
               input [4:0] iAddr,
	    output reg signed [7:0]  iW1,iW2,iW3,iW4,iW5,iW6,iW7,iW8,iW9,iW10,iW11,iW12,iW13,iW14,iW15,iW16,iW17,iW18,iW19,iW20,iW21,iW22,iW23,iW24,iW25);


wire [24:0] en;

assign en[0] = (iAddr==1 && iWren==1)?1:0;
assign en[1] = (iAddr==2 && iWren==1)?1:0;
assign en[2] = (iAddr==3 && iWren==1)?1:0;
assign en[3] = (iAddr==4 && iWren==1)?1:0;
assign en[4] = (iAddr==5 && iWren==1)?1:0;
assign en[5] = (iAddr==6 && iWren==1)?1:0;
assign en[6] = (iAddr==7 && iWren==1)?1:0;
assign en[7] = (iAddr==8 && iWren==1)?1:0;
assign en[8] = (iAddr==9 && iWren==1)?1:0;
assign en[9] = (iAddr==10 && iWren==1)?1:0;
assign en[10] = (iAddr==11 && iWren==1)?1:0;
assign en[11] = (iAddr==12 && iWren==1)?1:0;
assign en[12] = (iAddr==13 && iWren==1)?1:0;
assign en[13] = (iAddr==14 && iWren==1)?1:0;
assign en[14] = (iAddr==15 && iWren==1)?1:0;
assign en[15] = (iAddr==16 && iWren==1)?1:0;
assign en[16] = (iAddr==17 && iWren==1)?1:0;
assign en[17] = (iAddr==18 && iWren==1)?1:0;
assign en[18] = (iAddr==19 && iWren==1)?1:0;
assign en[19] = (iAddr==20 && iWren==1)?1:0;
assign en[20] = (iAddr==21 && iWren==1)?1:0;
assign en[21] = (iAddr==22 && iWren==1)?1:0;
assign en[22] = (iAddr==23 && iWren==1)?1:0;
assign en[23] = (iAddr==24 && iWren==1)?1:0;
assign en[24] = (iAddr==25 && iWren==1)?1:0;

	

//////////en=1
always@(posedge iCLK, negedge iRSTn)
begin
	if(!iRSTn)
	iW1 <= 0;
        else if (en[0])
	iW1 <= iWeight;
	
end

//////////en=2
always@(posedge iCLK, negedge iRSTn)
begin
	if(!iRSTn)
	iW2 <= 0;
        else if (en[1] )
	iW2 <= iWeight;
	
end

//////////en=3
always@(posedge iCLK, negedge iRSTn)
begin
	if(!iRSTn)
	iW3 <= 0;
        else if (en[2])
	iW3 <= iWeight;
	
end

//////////en=4
always@(posedge iCLK, negedge iRSTn)
begin
	if(!iRSTn)
	iW4 <= 0;
        else if (en[3])
	iW4 <= iWeight;
	
end

//////////en=5
always@(posedge iCLK, negedge iRSTn)
begin
	if(!iRSTn)
	iW5 <= 0;
        else if (en[4])
	iW5 <= iWeight;
	
end

//////////en=6
always@(posedge iCLK, negedge iRSTn)
begin
	if(!iRSTn)
	iW6 <= 0;
        else if (en[5])
	iW6 <= iWeight;
	
end

//////////en=7
always@(posedge iCLK, negedge iRSTn)
begin
	if(!iRSTn)
	iW7 <= 0;
        else if (en[6])
	iW7 <= iWeight;
	
end

//////////en=8
always@(posedge iCLK, negedge iRSTn)
begin
	if(!iRSTn)
	iW8 <= 0;
        else if (en[7])
	iW8 <= iWeight;
	
end

//////////en=9
always@(posedge iCLK, negedge iRSTn)
begin
	if(!iRSTn)
	iW9 <= 0;
        else if (en[8])
	iW9 <= iWeight;
	
end

//////////en=10
always@(posedge iCLK, negedge iRSTn)
begin
	if(!iRSTn)
	iW10 <= 0;
        else if (en[9])
	iW10 <= iWeight;
	
end

//////////en=11
always@(posedge iCLK, negedge iRSTn)
begin
	if(!iRSTn)
	iW11 <= 0;
        else if (en[10])
	iW11 <= iWeight;
	
end

//////////en=12
always@(posedge iCLK, negedge iRSTn)
begin
	if(!iRSTn)
	iW12 <= 0;
        else if (en[11])
	iW12 <= iWeight;
	
end

//////////en=13
always@(posedge iCLK, negedge iRSTn)
begin
	if(!iRSTn)
	iW13 <= 0;
        else if (en[12])
	iW13 <= iWeight;
	
end

//////////en=14
always@(posedge iCLK, negedge iRSTn)
begin
	if(!iRSTn)
	iW14 <= 0;
        else if (en[13])
	iW14 <= iWeight;
	
end

//////////en=15
always@(posedge iCLK, negedge iRSTn)
begin
	if(!iRSTn)
	iW15 <= 0;
        else if (en[14])
	iW15 <= iWeight;
	
end

//////////en=16
always@(posedge iCLK, negedge iRSTn)
begin
	if(!iRSTn)
	iW16 <= 0;
        else if (en[15])
	iW16 <= iWeight;
	
end

//////////en=17
always@(posedge iCLK, negedge iRSTn)
begin
	if(!iRSTn)
	iW17 <= 0;
        else if (en[16])
	iW17 <= iWeight;
	
end

//////////en=18
always@(posedge iCLK, negedge iRSTn)
begin
	if(!iRSTn)
	iW18 <= 0;
        else if (en[17])
	iW18 <= iWeight;
	
end

//////////en=19
always@(posedge iCLK, negedge iRSTn)
begin
	if(!iRSTn)
	iW19 <= 0;
        else if (en[18])
	iW19 <= iWeight;
	
end

//////////en=20
always@(posedge iCLK, negedge iRSTn)
begin
	if(!iRSTn)
	iW20 <= 0;
        else if (en[19])
	iW20 <= iWeight;
	
end

//////////en=21
always@(posedge iCLK, negedge iRSTn)
begin
	if(!iRSTn)
	iW21 <= 0;
        else if (en[20])
	iW21 <= iWeight;
	
end

//////////en=22
always@(posedge iCLK, negedge iRSTn)
begin
	if(!iRSTn)
	iW22 <= 0;
        else if (en[21])
	iW22 <= iWeight;
	
end

//////////en=23
always@(posedge iCLK, negedge iRSTn)
begin
	if(!iRSTn)
	iW23 <= 0;
        else if (en[22])
	iW23 <= iWeight;
	
end

//////////en=24
always@(posedge iCLK, negedge iRSTn)
begin
	if(!iRSTn)
	iW24 <= 0;
        else if (en[23] )
	iW24 <= iWeight;
	
end

//////////en=25
always@(posedge iCLK, negedge iRSTn)
begin
	if(!iRSTn)
	iW25 <= 0;
        else if (en[24])
	iW25 <= iWeight;
	
end
endmodule







