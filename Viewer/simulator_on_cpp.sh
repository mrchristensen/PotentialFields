cd ../Robot
./robot false navigate > robotOutput.txt &
cd ../AgentCpp
./agentCpp false navigate > agentOutput.txt &
cd ../MundoVerdadero/SimCode
./sim > simOutput.txt &
