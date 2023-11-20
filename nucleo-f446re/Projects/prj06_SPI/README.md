in this project i use spi2 as master and spi3 slave on one micro
##pins
 i joind miso to miso mosi to mosi and ck o ck and 
 selectone gpio_output as a cs(chipselect). and conect cs to nss in slave.

##program
  actived spi3 intrupt.
 so i write the recieve data in intrupt trade.
  use a whilw loop after transmit command to wait until finish the transmiting data
 
 ## more important point is prescaler 
 prescaler should be 256 in master.
