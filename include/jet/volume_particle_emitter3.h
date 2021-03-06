// Copyright (c) 2016 Doyub Kim

#ifndef INCLUDE_JET_VOLUME_PARTICLE_EMITTER3_H_
#define INCLUDE_JET_VOLUME_PARTICLE_EMITTER3_H_

#include <jet/bounding_box3.h>
#include <jet/implicit_surface3.h>
#include <jet/particle_emitter3.h>
#include <jet/point_generator3.h>
#include <limits>
#include <memory>
#include <random>

namespace jet {

//!
//! \brief 3-D volumetric particle emitter.
//!
//! This class emits particles from volumetric geometry.
//!
class VolumeParticleEmitter3 final : public ParticleEmitter3 {
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
    VolumeParticleEmitter3(
        const ImplicitSurface3Ptr& implicitSurface,
        const BoundingBox3D& bounds,
        double spacing,
        const Vector3D& initialVel = Vector3D(),
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
        const ParticleSystemData3Ptr& particles) override;

    //!
    //! \brief      Sets the point generator.
    //!
    //! This function sets the point generator that defines the pattern of the
    //! point distribution within the volume.
    //!
    //! \param[in]  newPointsGen The new points generator.
    //!
    void setPointGenerator(const PointGenerator3Ptr& newPointsGen);

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
    Vector3D initialVelocity() const;

    //! Returns the initial velocity of the particles.
    void setInitialVelocity(const Vector3D& newInitialVel);

 private:
    std::mt19937 _rng;

    ImplicitSurface3Ptr _implicitSurface;
    BoundingBox3D _bounds;
    double _spacing;
    Vector3D _initialVel;
    PointGenerator3Ptr _pointsGen;

    size_t _maxNumberOfParticles = std::numeric_limits<size_t>::max();
    size_t _numberOfEmittedParticles = 0;

    double _jitter = 0.0;
    bool _isOneShot = true;
    bool _allowOverlapping = false;

    void emit(
        const ParticleSystemData3Ptr& particles,
        Array1<Vector3D>* newPositions,
        Array1<Vector3D>* newVelocities);

    double random();
};

typedef std::shared_ptr<VolumeParticleEmitter3> VolumeParticleEmitter3Ptr;

}  // namespace jet

#endif  // INCLUDE_JET_VOLUME_PARTICLE_EMITTER3_H_
