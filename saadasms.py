from twilio.rest import Client

# Your Account SID from twilio.com/console
account_sid = "enter your SID here"
# Your Auth Token from twilio.com/console
auth_token  = "enter your Auth Token here"

client = Client(account_sid, auth_token)

message = client.messages.create(
    to="enter your own mobile number here", 
    from_="enter mobile number you got from twilio here",
    body="Alert! Movment Detected! Recording started")

