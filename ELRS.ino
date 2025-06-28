void elrs_init(){
  crsf = new CRSFforArduino(&Serial6, PC7,PC6); // define serial pin in this section too
    if (!crsf->begin())
    {
      crsf->end();

      delete crsf;
      crsf = nullptr;

      // Serial.println("CRSF for Arduino initialisation failed!");
      while (1)
      {
        // delay(10);
      }
    }
  rcChannelCount = rcChannelCount > crsfProtocol::RC_CHANNEL_COUNT ? crsfProtocol::RC_CHANNEL_COUNT : rcChannelCount;
  crsf->setRcChannelsCallback(onReceiveRcChannels);
}


void elrs_update(){
  crsf->update();
}


void onReceiveRcChannels(serialReceiverLayer::rcChannels_t *rcChannels)
{
  if (rcChannels->failsafe == false)
  {
    /* Print RC channels every 100 ms. */
    unsigned long thisTime = millis();
    static unsigned long lastTime = millis();

    /* Compensate for millis() overflow. */
    if (thisTime < lastTime)
    {
      lastTime = thisTime;
    }

    if (thisTime - lastTime >= 100)
    {
      lastTime          = thisTime;
      roll_channel      = crsf->rcToUs(crsf->getChannel(1));
      pitch_channel     = crsf->rcToUs(crsf->getChannel(2));
      throttle_channel  = crsf->rcToUs(crsf->getChannel(3));
      yaw_channel       = crsf->rcToUs(crsf->getChannel(4));
      ch5_channel       = crsf->rcToUs(crsf->getChannel(5));
      ch6_channel       = crsf->rcToUs(crsf->getChannel(6));
      ch7_channel       = crsf->rcToUs(crsf->getChannel(7));
      ch8_channel       = crsf->rcToUs(crsf->getChannel(8));
    }
  }
}