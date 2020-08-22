

#pragma once


namespace resident
{


   class animation_disco :
      virtual public animation
   {
   public:


      class llama :
      virtual public simple_object
      {
      public:

         int 		m_iPerson;
         double   m_dSize;
         double   m_dSpeed;
         double   m_dColor;
         double   m_dColorSpeed;
         int      m_iOffset;
         rect     m_rect;
         int      m_iLastTop;
         double                           m_dVel;
         image                 m_image;
         image                 m_imageHead;

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

      int                              m_iPerson;
      rect                             m_rectDisc;
      int                              m_iLastTop2;
      image                m_imageDiscoBall;
      image                 m_imagePerson;
      __pointera(::resident::user)            m_usera;
      int                              m_iLlamaFloor;
      int                              m_iLlama;
      __pointera(llama)                       m_llama;
      tick                            m_tickLastAddLlama;
      tick                            m_tickLlama;

      image                 m_imageLights;
      array < light >                  m_lighta;
      size                             m_sizeLight;
      double                           m_dLightAperture;
      double                           m_dBallDistance;
      double                           m_dPhase;
      double                           m_dDiscoColor;
      image                 m_imageDisco;



      animation_disco(main_stage * pmainstage);
      ~animation_disco();



      virtual void defer_add_llama();

      virtual bool on_started() override;

      virtual void _001OnDrawBefore(::draw2d::graphics * pgraphics) override;

      virtual void _001OnDrawAfter(::draw2d::graphics * pgraphics) override;


   };


} // namespace resident



