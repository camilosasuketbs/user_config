

#pragma once


namespace resident
{


   class animation_llama :
      virtual public animation
   {
   public:


      class llama
      {
      public:

         double   m_dSize;
         double   m_dSpeed;
         double   m_dColor;
         double   m_dColorSpeed;
         int      m_iOffset;
         rect     m_rect;
         int      m_iLastTop;
         double                           m_dVel;
         image                 m_image;

      };

      class light
      {
      public:
         point    m_pt;
         int      m_iBall;
         double   m_dPhase;
         double   m_dAngle;
         double   m_dColor;
         double   m_dColorSpeed;


      };


      rect                             m_rectDisc;
      int                              m_iLastTop2;
      image                 m_imageDiscoBall;
      image                 m_imageLlama;
      int                              m_iLlamaFloor;
      int                              m_iLlama;
      array < llama >                  m_llama;
      tick                             m_tickLastAddLlama;
      tick                             m_tickLlama;

      image                 m_imageLights;
      array < light >                  m_lighta;
      size                             m_sizeLight;
      double                           m_dLightAperture;
      double                           m_dBallDistance;
      double                           m_dPhase;
      double                           m_dDiscoColor;
      image                 m_imageDisco;



      animation_llama(main_stage * pmainstage);
      ~animation_llama();



      virtual void defer_add_llama();

      virtual bool on_started() override;

      virtual void _001OnDrawBefore(::draw2d::graphics * pgraphics) override;

      virtual void _001OnDrawAfter(::draw2d::graphics * pgraphics) override;


   };


} // namespace resident



