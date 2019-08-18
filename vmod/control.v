module control #(parameter xs=32, ws=5, stride=1)
		(input iCLK,iRSTn,
		 input iValid,
	         output oValid);

reg [4:0] i,j;
reg [3:0] col_next, row_next;

always@(posedge iCLK, negedge iRSTn)
begin
	if(!iRSTn)
	j <= 0;
	else if (iValid)
		begin
		if (j==xs-1)
		j <= 0;
		else
		j <= j+1;
		end
end

always@(posedge iCLK, negedge iRSTn)
begin
	if(!iRSTn)
	i <= 0;
	else if (iValid) 
        	begin
		if(i==xs-1 && j==xs-1)
		i <= 0;
		else
		i <= i+1;
 		end 
end

always@(posedge iCLK, negedge iRSTn)
begin
	if(!iRSTn)
	col_next <= ws-1;
         /* else if (iValid)
	begin	(j==xs-1)
	j <= 0;
	else
	j <= j+1;    */
end
endmodule





