# Packets

## Player

| Type       | Description      | 
| ------------- |:-------------| 
| string | name |
| uint8 | sides |
| float  | x position |
| float | y position | 
| float  | x velocity |
| float | y velocity | 

## HandshakeRequest

| Type       | Description      | 
| ------------- |:-------------|  
| string        | name |

## HandshakeResponse

| Type       | Description      | 
| ------------- |:-------------|  
| uint32       | id of player that user has control over |
| Player | The player that this user can now control |



## Update

| Type       | Description      | 
| ------------- |:-------------|  
| uint8 | type of update to preform (1 = remove enttiy (empty), 2 = update entity,  3=new polygon (Player), 4= update polygon)
| uint32       | id of entity to preform update on |
| corrosponding type | data corrosponding to the type indicated above | 


## Tick

| Type       | Description      | 
| ------------- |:-------------|  
| uin32 | tick_number |
| uin32 | num_updates |
| Update (x num_updates) | things to change before ticking | 
