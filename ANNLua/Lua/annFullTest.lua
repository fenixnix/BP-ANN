_G['os'] = nil
_G['io'] = nil
json = require 'json'

gUser = nil 

function init()
    _InitAnn(2)
end

function setUser(pUser) 
    gUser = pUser 
end

nerve = {
    [0] = 0, --bias
}
lambda = 0.05

function _Sigmoid(inputSignal)
    result = 1.0/(1.0+ math.exp(-1*inputSignal))
    return result
end

function _InitAnn(cnt)
   for i = cnt , 1, -1 do
    nerve[i] = math.random()
   end
end

function _Ask(inputSignal)
    local s = nerve[0]
    s = s + inputSignal[1]*nerve[1]
    s = s + inputSignal[2]*nerve[2]
    return _Sigmoid(s);
end

function _Teach(inputs,outputs)
    local O = _Ask(inputs)
    local E = O*(1.0-O)*(outputs[1]-O)
    nerve[1] = nerve[1]+lambda*E*inputs[1]
    nerve[2] = nerve[2]+lambda*E*inputs[2]
    nerve[0] = nerve[0]+lambda*E
end

function str2hex(pVar)  

    local hexstr  
    local charcode  
    local allhexstr = ''

    local bytes = pVar
  
    for i = 1, string.len(bytes) do  
  
        local charcode = tonumber(string.byte(bytes, i, i));  
        local hexstr = string.format("%02X", charcode);  
  
        allhexstr=allhexstr..hexstr  
    end  

    return allhexstr;  
end  

function hex2str(pVar)  
    local allhexstr = ''
    for i = 1, string.len(pVar) - 1, 2 do  
  
        local doublebytestr = string.sub(pVar, i, i+1);  
        local n = tonumber(doublebytestr, 16);  
        allhexstr=allhexstr..string.format("%c", n)
    end  
  
    return allhexstr
end

--[[
OriginNode Contract Code
{'input':[1,2,3,4]}
--]]
function getAsk(inputString)
    local str = hex2str(inputString)
    local input = json.decode(str)
    local O = _Ask(input['I'])
    return json.encode({output=O})
end

function teach(inputString)
    local str = hex2str(inputString)
    local IO = json.decode(str)
    local O = _Teach(IO['I'],IO['O'])
end

function getHelp()
    local str = 'Example:\nteach {"I":[0,0],"O":[0]}\nteach {"I":[0,1],"O":[0]}\nteach {"I":[1,0],"O":[0]}\nteach {"I":[1,1],"O":[1]}\ngetAsk {"I":[0,1]}\n'
    return str
end

--[[
SelfTest Code
--]]
function testTeach(times)
    print('Teach And')
    for i = times , 1, -1 
    do  
        _Teach({0,0},{0})
        _Teach({0,1},{0})
        _Teach({1,0},{0})
        _Teach({1,1},{1})
    end
end

function testAsk()
    print('Results:')
    result = _Ask({0,0})
    print(result)
    result = _Ask({0,1})
    print(result)
    result = _Ask({1,0})
    print(result)
    result = _Ask({1,1})
    print(result)
end

function test()
    print('Hello ANN!')
    _InitAnn(2)
    toolmodule.PrintTable(nerve)
    testAsk()

    testTeach(1000)
    toolmodule.PrintTable(nerve)
    testAsk()
    
    testTeach(1000)
    toolmodule.PrintTable(nerve)
    testAsk()
    
    testTeach(1000)
    toolmodule.PrintTable(nerve)
    testAsk()

    str = '{"I":[0,1]}'
    hex = str2hex(str)
    out = getAsk(hex)
    print(out)

    --teach('{"I":[2,3],"O":[1]}')
    teach('7b2249223a5b312c315d2c224f223a5b315d7d')
end

test()