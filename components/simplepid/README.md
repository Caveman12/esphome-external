# Example Use

`simple_pid:
  id: simple_pid_1
  setpoint: 70.0
  control_variable: room_temperature
  p: 1.0
  i: 2.0
  bias: 3.2
  direction: False
  enable: enable_pid
  `

## Required

`id:` 
`setpoint:` The Setpoiint to control to. Float value.
`control_variable:`
`p:` This is the propotional constant. It is multipled with the error value.

## Optional

`i:` This is a integral proption. The integral here is a rate per minute.
`direction:` Is a Binary value. True is the Direct acting direction and False is the reverse acting direction.
