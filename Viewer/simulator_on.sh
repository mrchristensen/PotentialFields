cd ../Robot
./robot false navigate > robotOutput.txt &
cd ../AgentPython
python3 agentPython.py false navigate > agentOutput.txt &
cd ../MundoVerdadero/SimCode
./sim > simOutput.txt &
