/*
 * fifo.sv
 */

module fifo
(
    input clk,
    input ce,       // clk enable
    input rst,

    input [DATA_W-1:0] w_data,   // input data
    input we,       // write enable
    output full,    // fifo full

    output [DATA_W-1:0] r_data,  // output data
    input re,       // read enable
    output empty    // fifo empty
);

    parameter DATA_W = 8;
    parameter ADDR_W = 2;

    logic [DATA_W-1:0] data [2**ADDR_W-1:0];
    logic [ADDR_W-1:0] write_ptr, read_ptr,
                       next_wptr, next_rptr;
    logic [ADDR_W:0] count /*verilator public*/;
    logic [ADDR_W:0] next_count;

    // read_ptr-1 because after re read_ptr is incremented
    assign r_data = data[read_ptr-1];

    always_ff @(posedge clk) if (ce) begin
        if (~full)
            data[write_ptr] <= w_data;
    end

    always_ff @(posedge clk) if (ce) begin
        if(rst) begin
            write_ptr <= 0;
            read_ptr <= 0;
        end else begin
            write_ptr <= next_wptr;
            read_ptr <= next_rptr;
        end
    end

    assign full = count==(2**ADDR_W);
    assign empty = count==0;

    always_ff @(posedge clk) if (ce) begin
        if (rst) begin
            count <= 0;
        end else begin
            count <= next_count;
        end
    end

    always_comb begin
        next_count = count;
        if (we && ~re && count<2**ADDR_W) begin
            next_count = count + 1;
        end else if(~we && re && count>0) begin
            next_count = count - 1;
        end
    end

    always_comb begin
        next_wptr = write_ptr;
        next_rptr = read_ptr;

        if (we && count<2**ADDR_W)
            next_wptr = write_ptr + 1;

        if (re && count>0)
            next_rptr = read_ptr + 1;
    end

endmodule