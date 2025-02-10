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
