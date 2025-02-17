#include <stdio.h>


int main(){
    int packet_size;          // Size of incoming packet
    int outflow_rate;        // Rate at which packets leave the bucket
    int bucket_capacity;     // Maximum capacity of the bucket
    int remaining_packets;   // Counter for number of input iterations
    int current_buffer = 0;  // current buffer size

    printf("Enter the bucket capacity, outflow rate and number of packets: ");
    scanf("%d %d %d", &bucket_capacity, &outflow_rate, &remaining_packets);

    while(remaining_packets>0){
        printf("Enter the packet size: ");
        scanf("%d", &packet_size);

        if(packet_size<=(bucket_capacity-current_buffer)){
            current_buffer+=packet_size;
            printf("Bucket Capacity is %d out of %d\n", current_buffer, bucket_capacity);
        }
        else{
            int dropped_packets = packet_size - (bucket_capacity - current_buffer);
            printf("Dropped %d of %d packets\n", dropped_packets, packet_size);

            
            current_buffer = bucket_capacity;
            printf("Bucket capacity is full\n");

        }

        int packets_to_remove = outflow_rate;
        if(current_buffer>=packets_to_remove){
            current_buffer-=outflow_rate;
        }
        else{
            current_buffer=0;
        }
        printf("After outgoing, There are %d out of %d packets left in buffer\n", 
            current_buffer, bucket_capacity);
        remaining_packets--;
    }
    return 0;
}


// 1.  **Initialization:** Get the bucket's `capacity`, `outflow_rate`, and the `number of packets` to process as input. Initialize the `current_buffer` to 0.

// 2.  **Packet Input:** For each incoming packet, read its `packet_size`.

// 3.  **Bucket Check:**
//     *   If the `packet_size` can fit within the remaining space in the `current_buffer` (i.e., `packet_size <= bucket_capacity - current_buffer`), add the packet to the bucket, increasing `current_buffer`.
//     *   Otherwise, calculate and report the number of `dropped_packets` due to overflow. Set the `current_buffer` to the `bucket_capacity` (as the bucket becomes full).

// 4.  **Outflow:**  Reduce the `current_buffer` by the `outflow_rate`. If the `current_buffer` is less than the `outflow_rate`, empty the bucket (`current_buffer = 0`).

// 5.  **Repeat:** Display the remaining packets in the buffer and decrement the `number of packets`. Repeat steps 2-4 until all packets are processed.
