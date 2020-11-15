void printMessage(String preMessage = "", float value = 0.0, String postMessage = "")
{
    Serial.println("");
    Serial.print(preMessage);
    Serial.print(" - ");
    Serial.print(value);
    Serial.print(postMessage);
    Serial.println("");
}

void printMessage(String preMessage = "")
{
    Serial.println(preMessage);
}
