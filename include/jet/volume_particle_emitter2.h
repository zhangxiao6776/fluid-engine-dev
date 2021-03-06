// Copyright (c) 2016 Doyub Kim

#ifndef INCLUDE_JET_VOLUME_PARTICLE_EMITTER2_H_
#define INCLUDE_JET_VOLUME_PARTICLE_EMITTER2_H_

#include <jet/constants.h>
#include <jet/bounding_box2.h>
#include <jet/implicit_surface2.h>
#include <jet/particle_emitter2.h>
#include <jet/point_generator2.h>
#include <limits>
#include <memory>
#include <random>

namespace jet {

//!
//! \brief 2-D volumetric particle emitter.
//!
//! This class emits particles from volumetric geometry.
//!
class VolumeParticleEmitter2 final : public ParticleEmitter2 {
 public:
    //!
    //! Constructs an emitter that spawns particles from given implicit surface
    //! which defines the volumetric geometry. Provided bounding box limits
    //! the particle generation region.
    //!
    //! \param[in]  implicitSurface         The implicit surface.
    //! \param[in]  bounds                  The bounding box.
    //! \param[in]  spacing                 The spacing between particles.
    //! \param[in]  initialVel              The initial velocity.
    //! \param[in]  maxNumberOfParticles    The max number of particles to be
    //!                                     emitted.
    //! \param[in]  jitter                  The jitter amount between 0 and 1.
    //! \param[in]  isOneShot               Set true if particles are emitted
    //!                                     just once.
    //! \param[in]  allowOverlapping        True if particles can be overlapped.
    //! \param[in]  seed                    The random seed.
    //!
    VolumeParticleEmitter2(
        const ImplicitSurface2Ptr& implicitSurface,
        const BoundingBox2D& bounds,
        double spacing,
        const Vector2D& initialVel = Vector2D(),
        size_t maxNumberOfParticles = kMaxSize,
        double jitter = 0.0,
        bool isOneShot = true,
        bool allowOverlapping = false,
        uint32_t seed = 0);

    //!
    //! Emits particles to the particle system data.
    //!
    //! \param[in]  frame     Current animation frame.
    //! \param[in]  particles The particle system data.
    //!
    void emit(
        const Frame& frame,
        const ParticleSystemData2Ptr& particles) override;

    //!
    //! \brief      Sets the point generator.
    //!
    //! This function sets the point generator that defines the pattern of the
    //! point distribution within the volume.
    //!
    //! \param[in]  newPointsGen The new points generator.
    //!
    void setPointGenerator(const PointGenerator2Ptr& newPointsGen);

    //! Returns jitter amount.
    double jitter() const;

    //! Sets jitter amount between 0 and 1.
    void setJitter(double newJitter);

    //! Returns true if particles should be emitted just once.
    bool isOneShot() const;

    //!
    //! \brief      Sets the flag to true if particles are emitted just once.
    //!
    //! If true is set, the emitter will generate particles only once even after
    //! multiple emit calls. If false, it will keep generating particles from
    //! the volumetric geometry. Default value is true.
    //!
    //! \param[in]  newValue True if particles should be emitted just once.
    //!
    void setIsOneShot(bool newValue);

    //! Returns trhe if particles can be overlapped.
    bool allowOverlapping() const;

    //!
    //! \brief      Sets the flag to true if particles can overlap each other.
    //!
    //! If true is set, the emitter will generate particles even if the new
    //! particles can find existing nearby particles within the particle
    //! spacing.
    //!
    //! \param[in]  newValue True if particles can be overlapped.
    //!
    void setAllowOverlapping(bool newValue);

    //! Returns max number of particles to be emitted.
    size_t maxNumberOfParticles() const;

    //! Sets the max number of particles to be emitted.
    void setMaxNumberOfParticles(size_t newMaxNumberOfParticles);

    //! Returns the spacing between particles.
    double spacing() const;

    //! Sets the spacing between particles.
    void setSpacing(double newSpacing);

    //! Sets the initial velocity of the particles.
    Vector2D initialVelocity() const;

    //! Returns the initial velocity of the particles.
    void setInitialVelocity(const Vector2D& newInitialVel);

 private:
    std::mt19937 _rng;

    ImplicitSurface2Ptr _implicitSurface;
    BoundingBox2D _bounds;
    double _spacing;
    Vector2D _initialVel;
    PointGenerator2Ptr _pointsGen;

    size_t _maxNumberOfParticles;
    size_t _numberOfEmittedParticles = 0;

    double _jitter = 0.0;
    bool _isOneShot = true;
    bool _allowOverlapping = false;

    void emit(
        const ParticleSystemData2Ptr& particles,
        Array1<Vector2D>* newPositions,
        Array1<Vector2D>* newVelocities);

    double random();
};

typedef std::shared_ptr<VolumeParticleEmitter2> VolumeParticleEmitter2Ptr;

}  // namespace jet

#endif  // INCLUDE_JET_VOLUME_PARTICLE_EMITTER2_H_
